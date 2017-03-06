/*
 *  Signal.h
 *
 *  A lightweight signals and slots implementation using fast delegates
 *
 */
#ifndef __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
#define __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C

#include "RTypes.h"
#include "RDelegate.h"
#include "RForwardList.h"
#include "RSpinLocker.h"

enum RConnectionType
{
  /// If the signal is emitted from a different thread than the receiving
  /// object the signal is blocked, behaving as BlockedConnection. Otherwise,
  /// the slot is invoked directly, behaving as DirectConnection. The type of
  /// connection is determined when the signal is connected.
  AutoConnection,
  DirectConnection,
  BlockedConnection,
};

template <class T>
class RConnection
{
public:
  typedef T DelegateType;

  RConnection(const DelegateType &delegate, uint8_t aType=AutoConnection)

    : mDelegate(delegate), mType(aType)
  {
  }

  RConnection(const RConnection &other)
    : mDelegate(other.mDelegate), mType(other.mType)
  {
  }

  DelegateType mDelegate;
  uint8_t      mType;
};

// Declare RSignal as a class template.  It will be specialized
// later for all number of arguments.
template <typename Signature>
class RSignal;

template <class R, class ... ParamTypes>
class RSignal<R(ParamTypes ...)>
{
public:
  typedef typename Rt::Delegate<R(ParamTypes ...)>::BaseType _Delegate;
  typedef RConnection<_Delegate>                             Connection;

private:
  typedef RForwardList<Connection> DelegateList;

public:
  void
  connect(const _Delegate &delegate)
  {
    R_MAKE_SPINLOCKER();
    mDelegateList.pushFront(Connection(delegate));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    connect(Rt::MakeDelegate(obj, func));
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

    mDelegateList.pushFront(Connection(Rt::MakeDelegate(receiver, func),
                                       connectionType));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    connect(Rt::MakeDelegate(obj, func));
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

    mDelegateList.pushFront(Connection(Rt::MakeDelegate(receiver, func),
                                       connectionType));
  }

  void
  connect(R (*functionToBind)(ParamTypes ...))
  {
    connect(Rt::Delegate<R(ParamTypes ...)>(functionToBind));
  }

  void
  disconnect(_Delegate delegate)
  {
    R_MAKE_SPINLOCKER();

    auto it = mDelegateList.beforeBegin();
    typename DelegateList::iterator nextIt;

    while(1)
    {
      nextIt = it + 1;

      if(nextIt == mDelegateList.end())
      {
        break;
      }

      if((*nextIt).mDelegate == delegate)
      {
        mDelegateList.eraseAfter(it);
      }

      it = nextIt;
    }
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    disconnect(Rt::MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    disconnect(Rt::MakeDelegate(obj, func));
  }

  void
  clear()
  {
    R_MAKE_SPINLOCKER();
    mDelegateList.clear();
  }

  void
  emit(ParamTypes ... params) const
  {
    for(auto it = mDelegateList.begin(); it != mDelegateList.end(); )
    {
      Connection &connection = *it;

      if(BlockedConnection == connection.mType)
      {
        R_MAKE_SPINLOCKER();
        connection.mDelegate(params ...);
      }
      else
      {
        connection.mDelegate(params ...);
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
    return mDelegateList.empty();
  }

private:
  DelegateList mDelegateList;
};

#endif //__INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
