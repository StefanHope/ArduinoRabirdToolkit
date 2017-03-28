#ifndef __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
#define __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF

#include "RSpinLocker.h"

template <class T>
class RAtomicInteger
{
public:
  RAtomicInteger(T value=0)
  {
    R_MAKE_SPINLOCKER();

    mValue = value;
  }

  RAtomicInteger(const RAtomicInteger &other)
  {
    R_MAKE_SPINLOCKER();

    mValue = other.mValue;
  }

  bool
  addIfLessThan(T compareValue, T valueToAdd)
  {
    R_MAKE_SPINLOCKER();

    if(mValue < compareValue)
    {
      mValue += valueToAdd;
      return true;
    }

    return false;
  }

  bool
  addIfLargeThan(T compareValue, T valueToAdd)
  {
    R_MAKE_SPINLOCKER();

    if(mValue > compareValue)
    {
      mValue += valueToAdd;
      return true;
    }

    return false;
  }

  bool
  setIfLessThan(T compareValue, T newValue)
  {
    R_MAKE_SPINLOCKER();

    if(mValue < compareValue)
    {
      mValue = newValue;
      return true;
    }

    return false;
  }

  bool
  setIfLargeThan(T compareValue, T newValue)
  {
    R_MAKE_SPINLOCKER();

    if(mValue > compareValue)
    {
      mValue = newValue;
      return true;
    }

    return false;
  }

  bool
  deref()
  {
    R_MAKE_SPINLOCKER();
    --mValue;
    return mValue != 0;
  }

  bool
  ref()
  {
    R_MAKE_SPINLOCKER();
    ++mValue;
    return mValue != 0;
  }

  void
  store(T newValue)
  {
    R_MAKE_SPINLOCKER();
    mValue = newValue;
  }

  T
  load() const
  {
    R_MAKE_SPINLOCKER();
    return mValue;
  }

  operator T() const
  {
    R_MAKE_SPINLOCKER();
    return mValue;
  }

  T
  operator &=(T valueToAnd)
  {
    R_MAKE_SPINLOCKER();
    mValue &= valueToAnd;
    return mValue;
  }

  T
  operator ++()
  {
    R_MAKE_SPINLOCKER();
    return ++mValue;
  }

  T
  operator ++(int)
  {
    R_MAKE_SPINLOCKER();
    return mValue++;
  }

  T
  operator +=(T valueToAdd)
  {
    R_MAKE_SPINLOCKER();
    return mValue += valueToAdd;
  }

  T
  operator --()
  {
    R_MAKE_SPINLOCKER();
    return --mValue;
  }

  T
  operator --(int)
  {
    R_MAKE_SPINLOCKER();
    return mValue--;
  }

  T
  operator -=(T valueToSub)
  {
    R_MAKE_SPINLOCKER();
    return mValue -= valueToSub;
  }

  RAtomicInteger &
  operator =(const RAtomicInteger &other)
  {
    R_MAKE_SPINLOCKER();
    mValue = other.mValue;
    return *this;
  }

  RAtomicInteger &
  operator =(T newValue)
  {
    R_MAKE_SPINLOCKER();
    mValue = newValue;
    return *this;
  }

  T
  operator ^=(T valueToXor)
  {
    R_MAKE_SPINLOCKER();
    return mValue ^= valueToXor;
  }

  T
  operator |=(T valueToOr)
  {
    R_MAKE_SPINLOCKER();
    return mValue |= valueToOr;
  }

private:
  T mValue;
};

#endif // __INCLUDED_2A3F0CB05FA111E6A54200F1F38F93EF
