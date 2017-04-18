/*
 *  Signal.h
 *
 *  A lightweight signals and slots implementation using fast slots
 *
 */
#ifndef __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
#define __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C

#include "RTypes.h"
#include "RSlot.h"
#include "RForwardList.h"
#include "RSpinLocker.h"
#include "RMain.h"
#include "REvent.h"
#include "RMetaCallEvent.h"

enum RConnectionType
{
  /// If the signal is emitted from a different thread than the receiving
  /// object the signal is blocked, behaving as BlockedConnection. Otherwise,
  /// the slot is invoked directly, behaving as DirectConnection. The type of
  /// connection is determined when the signal is connected.
  AutoConnection,
  DirectConnection,
  ObjectConnection,
  BlockedConnection,
};

template <class T>
class RConnection
{
public:
  typedef T SlotType;

  RConnection(const SlotType &slot, uint8_t aType=AutoConnection)

    : mSlot(slot), mType(aType)
  {
  }

  RConnection(const RConnection &other)
    : mSlot(other.mSlot), mType(other.mType)
  {
  }

  SlotType mSlot;
  uint8_t  mType;
};

// Declare RSignal as a class template.  It will be specialized
// later for all number of arguments.
template <typename Signature>
class RSignal;

template <class R, class ... ParamTypes>
class RSignal<R(ParamTypes ...)>
{
public:
  typedef typename Rt::Slot<R(ParamTypes ...)>::BaseType _Slot;
  typedef RConnection<_Slot>                             Connection;

private:
  typedef RForwardList<Connection> ConnectionList;

public:
  void
  connect(const _Slot &slot)
  {
    R_MAKE_SPINLOCKER();
    mConnections.pushFront(Connection(slot));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    connect(rMakeSlot(obj, func));
  }

  template <class X>
  void
  connect(RObject *sender, RObject *receiver, void (X::*func)(ParamTypes ...))
  {
    R_MAKE_SPINLOCKER();

    uint8_t connectionType = BlockedConnection;

    if(rIsObjectInSameThread(sender, receiver))
    {
      connectionType = DirectConnection;
    }

    mConnections.pushFront(Connection(rMakeSlot(
                                        static_cast<X *>(receiver), func),
                                      connectionType));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    connect(rMakeSlot(obj, func));
  }

  template <class X>
  void
  connect(RObject *sender, RObject *receiver, void (X::*func)(
            ParamTypes ...) const)
  {
    R_MAKE_SPINLOCKER();

    uint8_t connectionType = BlockedConnection;

    if(rIsObjectInSameThread(sender, receiver))
    {
      connectionType = DirectConnection;
    }

    mConnections.pushFront(Connection(rMakeSlot(
                                        static_cast<X *>(receiver), func),
                                      connectionType));
  }

  void
  connect(R (*functionToBind)(ParamTypes ...))
  {
    connect(Rt::Slot<R(ParamTypes ...)>(functionToBind));
  }

  void
  disconnect(_Slot slot)
  {
    R_MAKE_SPINLOCKER();

    auto it = mConnections.beforeBegin();
    typename ConnectionList::iterator nextIt;

    while(1)
    {
      nextIt = it + 1;

      if(nextIt == mConnections.end())
      {
        break;
      }

      if((*nextIt).mSlot == slot)
      {
        mConnections.eraseAfter(it);
      }

      it = nextIt;
    }
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    disconnect(rMakeSlot(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    disconnect(rMakeSlot(obj, func));
  }

  void
  clear()
  {
    R_MAKE_SPINLOCKER();
    mConnections.clear();
  }

  void
  emit(ParamTypes ... params) const
  {
    for(auto it = mConnections.begin(); it != mConnections.end(); )
    {
      Connection &connection = *it;

      if(BlockedConnection == connection.mType)
      {
        // FIXME: We must lock both threads of sender and receiver here!
        connection.mSlot(params ...);
      }
      else
      {
        connection.mSlot(params ...);
      }

      it++;
    }
  }

  void
  operator ()(ParamTypes ... params) const
  {
    emit(params ...);
  }

  bool
  empty() const
  {
    return mConnections.empty();
  }

private:
  ConnectionList mConnections;
};

/**
 * Specific to "void()" style
 */
template <>
class RSignal<void()>
{
public:
  typedef typename Rt::Slot<void ()>::BaseType _Slot;
  typedef RConnection<_Slot>                   Connection;

private:
  typedef RForwardList<Connection> ConnectionList;

public:
  void
  connect(const _Slot &slot)
  {
    R_MAKE_SPINLOCKER();
    mConnections.pushFront(Connection(slot));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)())
  {
    connect(rMakeSlot(obj, func));
  }

  template <class X>
  void
  connect(RObject *sender, RObject *receiver, void (X::*func)())
  {
    R_MAKE_SPINLOCKER();

    uint8_t connectionType = BlockedConnection;

    if(rIsObjectInSameThread(sender, receiver))
    {
      connectionType = ObjectConnection;
    }

    mConnections.pushFront(Connection(rMakeSlot(
                                        static_cast<X *>(receiver), func),
                                      connectionType));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)() const)
  {
    connect(rMakeSlot(obj, func));
  }

  template <class X>
  void
  connect(RObject *sender, RObject *receiver, void (X::*func)(
            ) const)
  {
    R_MAKE_SPINLOCKER();

    uint8_t connectionType = BlockedConnection;

    if(rIsObjectInSameThread(sender, receiver))
    {
      connectionType = ObjectConnection;
    }

    mConnections.pushFront(Connection(rMakeSlot(
                                        static_cast<X *>(receiver), func),
                                      connectionType));
  }

  void
  connect(void (*functionToBind)())
  {
    connect(Rt::Slot<void()>(functionToBind));
  }

  void
  disconnect(_Slot slot)
  {
    R_MAKE_SPINLOCKER();

    auto it = mConnections.beforeBegin();
    typename ConnectionList::iterator nextIt;

    while(1)
    {
      nextIt = it + 1;

      if(nextIt == mConnections.end())
      {
        break;
      }

      if((*nextIt).mSlot == slot)
      {
        mConnections.eraseAfter(it);
      }

      it = nextIt;
    }
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)())
  {
    disconnect(rMakeSlot(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)() const)
  {
    disconnect(rMakeSlot(obj, func));
  }

  void
  clear()
  {
    R_MAKE_SPINLOCKER();
    mConnections.clear();
  }

  void
  emit() const
  {
    for(auto it = mConnections.begin(); it != mConnections.end(); )
    {
      Connection &connection = *it;

      if(BlockedConnection == connection.mType)
      {
        // FIXME: We must lock both threads of sender and receiver here!
        connection.mSlot();
      }
      else if(ObjectConnection == connection.mType)
      {
        auto closure =
          (const _Slot::ClosureType &)(connection.mSlot.GetMemento());
        auto closureThis = closure.GetClosureThis();

        // If type equal to ObjectConnection, that means it must be object type!
        rPostEvent(reinterpret_cast<RObject *>(closureThis),
                   rMakeEvent<RMetaCallEvent,
                              REvent::MetaCall>(connection.mSlot));
      }
      else
      {
        connection.mSlot();
      }

      it++;
    }
  }

  void
  operator ()() const
  {
    emit();
  }

  bool
  empty() const
  {
    return mConnections.empty();
  }

private:
  ConnectionList mConnections;
};

#endif //__INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
