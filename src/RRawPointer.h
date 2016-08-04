#ifndef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
#define __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF

#include "RTypes.h"

template <class T>
class RRawPointer
{
public:
  RRawPointer(): mPtr(0)
  {
  }

  RRawPointer(const T *ptr): mPtr(rShortenPtr(ptr))
  {
  }

  ~RRawPointer()
  {
  }

  T *
  data() const
  {
    return rLengthenPtr<T *>(mPtr);
  }

  bool
  isNull() const
  {
    return (mPtr == 0);
  }

  void
  clear()
  {
    mPtr = 0;
  }

  void
  reset()
  {
    clear();
  }

  void
  reset(T *ptr)
  {
    mPtr = rShortenPtr(ptr);
  }

  T *
  operator ->() const
  {
    return data();
  }

  operator bool() const
  {
    return !isNull();
  }

  bool
  operator!() const
  {
    return isNull();
  }

  T &
  operator*() const
  {
    return *data();
  }

  RRawPointer<T> &
  operator=(const RRawPointer<T> &other)
  {
    mPtr = other.mPtr;
    return *this;
  }

private:
  uintptr_t mPtr;
};

#endif // #ifdef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
