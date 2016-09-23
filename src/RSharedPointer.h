#ifndef __INCLUDED_B56797CC644611E6933700F1F38F93EF
#define __INCLUDED_B56797CC644611E6933700F1F38F93EF

#include "RTypes.h"
#include "RRawPointer.h"
#include "RAtomicInteger.h"

namespace Rt
{
template <class T, class Counter, class Deleter>
struct RSharedPointerContext
{
public:
  RSharedPointerContext() : ptr(NULL)
  {
  }

  T *     ptr;
  Deleter deleter;
  Counter counter;
};
}

template <class DerivedType_, class T>
class RBasicSharedPointer
  : public RBasicRawPointer<DerivedType_, T>
{
public:
  typedef RBasicRawPointer<DerivedType_, T>              BaseType;
  typedef typename BaseType::StorageType                 StorageType;
  typedef typename BaseType::DerivedType                 DerivedType;
  typedef void                                           (*Deleter)(T *ptr);
  typedef RAtomicInteger<rnumber>                        Counter;
  typedef RPointerDeleter<T>                             DefaultDeleterType;
  typedef Rt::RSharedPointerContext<T, Counter, Deleter> Context;

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
    auto context = getContext();

    if(context && context->ptr)
    {
      ++context->counter;
    }
  }

  void
  clear()
  {
    auto context = getContext();

    if(context && context->ptr)
    {
      if((--context->counter) <= 0)
      {
        if(context->deleter)
        {
          context->deleter(context->ptr);
        }

        delete context;
      }
    }

    BaseType::clear();
  }

  void
  reset(T *ptr=NULL, Deleter deleter=&DefaultDeleterType::cleanup)
  {
    BaseType::reset(ptr);

    if(ptr)
    {
      if(deleter)
      {
        deleter = &DefaultDeleterType::cleanup;
      }

      auto context = getContext();

      context->deleter = deleter;
    }
  }

  inline
  StorageType
  toStorageType(const T *ptr)
  {
    if(NULL == ptr)
    {
      return 0;
    }

    auto context = new Context();

    context->ptr = ptr;
    context->counter++;

    return BaseType::toStorageType(reinterpret_cast<T *>(context));
  }

  inline
  T *
  fromStorageType(StorageType ptr)
  {
    auto context = reinterpret_cast<Context *>(BaseType::fromStorageType(ptr));

    if(NULL == context)
    {
      return NULL;
    }

    return context->ptr;
  }

private:
  Context *
  getContext()
  {
    return reinterpret_cast<Context *>(
      BaseType::fromStorageType(BaseType::internalStorage()));
  }
};

template <class T>
class RSharedPointer
  : public RBasicSharedPointer<RSharedPointer<T>, T>
{
public:
  typedef RBasicSharedPointer<RSharedPointer<T>, T> BaseType;

  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;
  typedef typename BaseType::Deleter     Deleter;

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
