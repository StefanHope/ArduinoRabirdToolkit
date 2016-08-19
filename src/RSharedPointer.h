#ifndef __INCLUDED_B56797CC644611E6933700F1F38F93EF
#define __INCLUDED_B56797CC644611E6933700F1F38F93EF

#include "RTypes.h"
#include "RRawPointer.h"
#include "RAtomicInteger.h"

template <class DerivedType_, class T>
class RBasicSharedPointer
  : public RBasicRawPointer<DerivedType_, T>
{
public:
  typedef RBasicRawPointer<DerivedType_, T> BaseType;
  typedef typename BaseType::StorageType    StorageType;
  typedef typename BaseType::DerivedType    DerivedType;
  typedef void                              (*Deleter)(T *ptr);
  typedef RAtomicInteger<rnumber_t>         Counter;
  typedef RPointerDeleter<T>                DefaultDeleterType;

public:
  RBasicSharedPointer()
  {
    BaseType::getDerived()->reset(NULL, &DefaultDeleterType::cleanup);
  }

  RBasicSharedPointer(T *ptr)
  {
    BaseType::getDerived()->reset(ptr, &DefaultDeleterType::cleanup);
  }

  RBasicSharedPointer(T *ptr, Deleter deleter)
  {
    BaseType::getDerived()->reset(ptr, deleter);
  }

  RBasicSharedPointer(const DerivedType &other) : BaseType(other)
  {
    mDeleter = other.mDeleter;
    mCounter = other.mCounter;

    if(BaseType::getDerived()->data())
    {
      ++*mCounter;
    }
  }

  ~RBasicSharedPointer()
  {
    BaseType::getDerived()->clear();
  }

  void
  clear()
  {
    T *ptr = BaseType::getDerived()->data();

    if(NULL != ptr)
    {
      if((--*mCounter) <= 0)
      {
        mDeleter(ptr);

        delete mCounter.data();
      }
    }

    mDeleter = NULL;
    mCounter.reset();

    BaseType::clear();
  }

  void
  reset(T *ptr=NULL, Deleter deleter=&DefaultDeleterType::cleanup)
  {
    BaseType::reset(ptr);

    if(ptr)
    {
      if(NULL == deleter)
      {
        deleter = &DefaultDeleterType::cleanup;
      }

      mDeleter = deleter;
      mCounter.reset(new Counter());
      ++*mCounter;
    }
  }

private:
  RRawPointer<Counter> mCounter;
  Deleter mDeleter;
};

template <class T>
class RSharedPointer
  : public RBasicSharedPointer<RSharedPointer<T>, T>
{
public:
  typedef RBasicSharedPointer<RSharedPointer<T>, T> BaseType;
  typedef typename BaseType::StorageType            StorageType;
  typedef typename BaseType::DerivedType            DerivedType;
  typedef typename BaseType::Deleter                Deleter;

public:
  RSharedPointer() : BaseType()
  {
  }

  RSharedPointer(T *ptr) : BaseType(ptr)
  {
  }

  RSharedPointer(T *ptr, Deleter deleter) : BaseType(ptr, deleter)
  {
  }

  RSharedPointer(const DerivedType &other) : BaseType(other)
  {
  }
};

#endif // __INCLUDED_B56797CC644611E6933700F1F38F93EF
