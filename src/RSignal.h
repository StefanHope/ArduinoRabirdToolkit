/*
 *  Signal.h
 *
 *  A lightweight signals and slots implementation using fast delegates
 *
 */
#ifndef __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C
#define __INCLUDED_C5173AA242B211E6AA6EA088B4D1658C

#include "RDelegate.h"
#include "RForwardList.h"

// Declare RSignal as a class template.  It will be specialized
// later for all number of arguments.
template <typename Signature>
class RSignal;

template <class R, class ... ParamTypes>
class RSignal<R(ParamTypes ...)>
{
public:
  typedef typename Rt::Delegate<R(ParamTypes ...)>::BaseType _Delegate;

private:
  typedef RForwardList<_Delegate> DelegateList;

public:
  void
  connect(_Delegate delegate)
  {
    mDelegateList.pushFront(delegate);
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    mDelegateList.pushFront(Rt::MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  connect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    mDelegateList.pushFront(Rt::MakeDelegate(obj, func));
  }

  void
  connect(R (*functionToBind)(ParamTypes ...))
  {
    mDelegateList.pushFront(Rt::Delegate<R(ParamTypes ...)>(functionToBind));
  }

  void
  disconnect(_Delegate delegate)
  {
    mDelegateList.remove(delegate);
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...))
  {
    mDelegateList.remove(Rt::MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void
  disconnect(Y *obj, void (X::*func)(ParamTypes ...) const)
  {
    mDelegateList.remove(Rt::MakeDelegate(obj, func));
  }

  void
  clear()
  {
    mDelegateList.clear();
  }

  void
  emit(ParamTypes ... params) const
  {
    for(auto i = mDelegateList.begin(); i != mDelegateList.end();
        )
    {
      (*(i++))(params ...);
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
