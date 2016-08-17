#ifndef __INCLUDED_B56797CC644611E6933700F1F38F93EF
#define __INCLUDED_B56797CC644611E6933700F1F38F93EF

#include "RTypes.h"
#include "RRawPointer.h"
#include "RAtomicInteger.h"

template <class T>
class RSharedPointer
{
public:
  typedef void                      (*Deleter)(T *ptr);
  typedef RAtomicInteger<rnumber_t> Counter;

  RSharedPointer()
  {
  }

  RSharedPointer(T *ptr)
  {
    reset(ptr);
  }

  RSharedPointer(T *ptr, Deleter deleter)
  {
    reset(ptr, deleter);
  }

  RSharedPointer(const RSharedPointer<T> &other)
  {
    reset(other.mPtr, other.mDeleter, other.mCounter);

    if(mPtr)
    {
      ++*mCounter;
    }
  }

  ~RSharedPointer()
  {
    clear();
  }

  void
  clear()
  {
    if(mPtr && mDeleter)
    {
      (*mDeleter)(mPtr.data());
    }
    else
    {
      delete mPtr.data();
    }

    if((--*mCounter) <= 0)
    {
      delete mCounter.data();
    }

    mPtr.reset();
    mDeleter.reset();
    mCounter.reset();
  }

  T *
  data() const
  {
    return mPtr.data();
  }

  bool
  isNull() const
  {
    return mPtr.isNull();
  }

  void
  reset()
  {
    clear();
  }

  void
  reset(T *ptr)
  {
    clear();

    mPtr     = ptr;
    mDeleter = NULL;
    mCounter = new Counter();

    if(mPtr)
    {
      ++*mCounter;
    }
  }

  void
  reset(T *ptr, Deleter deleter)
  {
    reset(ptr);

    mDeleter = deleter;
  }

  void
  swap(RSharedPointer<T> &other)
  {
    RSharedPointer<T> temp;

    temp  = other;
    other = *this;
    *this = temp;
  }

  operator bool() const
  {
    return mPtr;
  }

  bool
  operator !() const
  {
    return !mPtr;
  }

  T &
  operator *() const
  {
    return *mPtr;
  }

  T *
  operator ->() const
  {
    return mPtr.data();
  }

  RSharedPointer<T> &
  operator =(const RSharedPointer<T> &other)
  {
    if(this == &other)
    {
      return *this;
    }

    reset(other.mPtr, other.mDeleter);
    return *this;
  }

private:
  RRawPointer<T> mPtr;

  RRawPointer<Deleter> mDeleter;
  RRawPointer<Counter> mCounter;
};

#endif // __INCLUDED_B56797CC644611E6933700F1F38F93EF
