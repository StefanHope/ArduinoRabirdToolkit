#ifndef __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
#define __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF

#include "RSpinLocker.h"

template <class T>
class RAtomicInteger
{
public:
  RAtomicInteger(T value=0)
  {
    RSpinLocker();

    mValue = value;
  }

  RAtomicInteger(const RAtomicInteger &other)
  {
    RSpinLocker();

    mValue = other.mValue;
  }

  bool
  deref()
  {
    RSpinLocker();
    --mValue;
    return mValue != 0;
  }

  bool
  ref()
  {
    RSpinLocker();
    ++mValue;
    return mValue != 0;
  }

  void
  store(T newValue)
  {
    RSpinLocker();
    mValue = newValue;
  }

  T
  load() const
  {
    RSpinLocker();
    return mValue;
  }

  operator T() const
  {
    RSpinLocker();
    return mValue;
  }

  T
  operator &=(T valueToAnd)
  {
    RSpinLocker();
    mValue &= valueToAnd;
    return mValue;
  }

  T
  operator ++()
  {
    RSpinLocker();
    return ++mValue;
  }

  T
  operator ++(int)
  {
    RSpinLocker();
    return mValue++;
  }

  T
  operator +=(T valueToAdd)
  {
    RSpinLocker();
    return mValue += valueToAdd;
  }

  T
  operator --()
  {
    RSpinLocker();
    return --mValue;
  }

  T
  operator --(int)
  {
    RSpinLocker();
    return mValue--;
  }

  T
  operator -=(T valueToSub)
  {
    RSpinLocker();
    return mValue -= valueToSub;
  }

  RAtomicInteger &
  operator =(const RAtomicInteger &other)
  {
    RSpinLocker();
    mValue = other.mValue;
    return *this;
  }

  RAtomicInteger &
  operator =(T newValue)
  {
    RSpinLocker();
    mValue = newValue;
    return *this;
  }

  T
  operator ^=(T valueToXor)
  {
    RSpinLocker();
    return mValue ^= valueToXor;
  }

  T
  operator |=(T valueToOr)
  {
    RSpinLocker();
    return mValue |= valueToOr;
  }

private:
  T mValue;
};

#endif // __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
