#ifndef __INCLUDED_B9852640644F11E6878D00F1F38F93EF
#define __INCLUDED_B9852640644F11E6878D00F1F38F93EF

#include "RBasicPointer.h"

template <class T>
class RScopedPointerDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    delete ptr;
  }
};

template <class T>
class RScopedPointerPodDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    free(ptr);
  }
};

template <class T>
class RScopedPointerArrayDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    delete[] ptr;
  }
};

template <class T, class CleanupType = RScopedPointerDeleter<T> >
class RScopedPointer
  : public RBasicPointer<RScopedPointer<T, CleanupType>, T, uintptr_t>
{
public:
  typedef uintptr_t StorageType;

  typedef RScopedPointer<T, CleanupType>          ThisType;
  typedef RBasicPointer<ThisType, T, StorageType> BaseType;

  RScopedPointer(T *ptr=0) : BaseType(ptr)
  {
  }

  RScopedPointer(ThisType &other) : BaseType(other)
  {
  }

  ~RScopedPointer()
  {
    BaseType::getThis()->clear();
  }

  void
  clear()
  {
    T *ptr = BaseType::getThis()->data();
    BaseType::clear();
    CleanupType::cleanup(ptr);
  }

  T *
  take()
  {
    T *ret = BaseType::getThis()->data();
    BaseType::getThis()->clear();

    return ret;
  }

  ThisType &
  operator =(const ThisType &other)
  {
    BaseType::getThis()->reset(other.take());

    return *this;
  }

protected:
  inline
  StorageType
  toStorageType(const T *ptr)
  {
    return rShortenPtr(ptr);
  }

  inline
  T *
  fromStorageType(StorageType ptr)
  {
    return rLengthenPtr<T *>(ptr);
  }

  friend BaseType;
};

#endif // __INCLUDED_B9852640644F11E6878D00F1F38F93EF
