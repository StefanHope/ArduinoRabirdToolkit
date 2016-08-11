#ifndef __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
#define __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF

#include "RSpinLock.h"

template <class T>
class RAtomicInteger
{
public:  
  RAtomicInteger(T value=0)
  {
    RSpinLock();

    mValue = value;
  }

  RAtomicInteger(const RAtomicInteger &other)
  {
    RSpinLock();

    mValue = other.mValue;
  }

  bool
  deref()
  {
    RSpinLock();
    -- mValue;
    return mValue != 0;
  }

  bool
  ref()
  {
    RSpinLock();
    ++ mValue;
    return mValue != 0;
  }

  void
  store(T newValue)
  {
    RSpinLock();
    mValue = newValue;
  }

  T load() const
  {
    RSpinLock();
    return mValue;
  }

  operator T() const
  {
    RSpinLock();
    return mValue;
  }

  T
  operator&=(T valueToAnd)
  {
    RSpinLock();
    mValue &= valueToAnd;
    return mValue;
  }

  T
  operator++()
  {
    RSpinLock();
    return ++ mValue;
  }

  T
  operator++(int)
  {
    RSpinLock();
    return mValue ++;
  }

  T
  operator+=(T valueToAdd)
  {
    RSpinLock();
    return mValue += valueToAdd;
  }

  T
  operator--()
  {
    RSpinLock();
    return -- mValue;
  }

  T
  operator--(int)
  {
    RSpinLock();
    return mValue --;
  }

  T
  operator-=(T valueToSub)
  {
    RSpinLock();
    return mValue -= valueToSub;
  }

  RAtomicInteger &
  operator=(const RAtomicInteger &other)
  {
    RSpinLock();
    mValue = other.mValue;
    return *this;
  }

  RAtomicInteger &
  operator=(T newValue)
  {
    RSpinLock();
    mValue = newValue;
    return *this;
  }

  T
  operator^=(T valueToXor)
  {
    RSpinLock();
    return mValue ^= valueToXor;
  }

  T
  operator|=(T valueToOr)
  {
    RSpinLock();
    return mValue |= valueToOr;
  }

private:
  T mValue;
};

#endif // __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
