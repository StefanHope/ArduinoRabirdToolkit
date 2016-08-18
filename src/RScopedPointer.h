#ifndef __INCLUDED_B9852640644F11E6878D00F1F38F93EF
#define __INCLUDED_B9852640644F11E6878D00F1F38F93EF

#include "RRawPointer.h"

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

template <class DerivedType, class T, class CleanupType>
class RBasicScopedPointer
  : public RBasicRawPointer<DerivedType, T>
{
public:
  typedef RBasicRawPointer<DerivedType, T> BaseType;

  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::ThisType    ThisType;

protected:
  // Don't allow create RBasicScopedPointer without any argument!
  RBasicScopedPointer();

public:
  RBasicScopedPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RBasicScopedPointer(ThisType &other) : BaseType(other.take())
  {
  }

  ~RBasicScopedPointer()
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
  friend BaseType;
};

template <class T, class CleanupType = RScopedPointerDeleter<T> >
class RScopedPointer
  : public RBasicScopedPointer<RScopedPointer<T, CleanupType>, T, CleanupType>
{
public:
  typedef RBasicScopedPointer<RScopedPointer<T, CleanupType>, T,
                              CleanupType> BaseType;
  typedef typename BaseType::StorageType
                                           StorageType;
  typedef typename BaseType::ThisType
                                           ThisType;

protected:
  // Don't allow create RScopedPointer without any argument!
  RScopedPointer();

public:
  RScopedPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RScopedPointer(ThisType &other) : BaseType(other)
  {
  }
};

#endif // __INCLUDED_B9852640644F11E6878D00F1F38F93EF
