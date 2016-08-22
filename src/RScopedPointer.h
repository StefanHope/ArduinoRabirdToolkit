#ifndef __INCLUDED_B9852640644F11E6878D00F1F38F93EF
#define __INCLUDED_B9852640644F11E6878D00F1F38F93EF

#include "RRawPointer.h"

template <class DerivedType_, class T, class CleanupType>
class RBasicScopedPointer
  : public RBasicRawPointer<DerivedType_, T>
{
public:
  typedef RBasicRawPointer<DerivedType_, T> BaseType;
  typedef typename BaseType::StorageType    StorageType;
  typedef typename BaseType::DerivedType    DerivedType;

protected:
  // Don't allow create RBasicScopedPointer without any argument!
  RBasicScopedPointer();

public:
  RBasicScopedPointer(T *ptr) : BaseType(ptr)
  {
  }

  RBasicScopedPointer(DerivedType &other) : BaseType(other.take())
  {
  }

  ~RBasicScopedPointer()
  {
    BaseType::getDerived()->clear();
  }

  void
  clear()
  {
    T *ptr = BaseType::getDerived()->data();

    BaseType::clear();
    CleanupType::cleanup(ptr);
  }

  T *
  take()
  {
    T *ret = BaseType::getDerived()->data();

    BaseType::getDerived()->clear();

    return ret;
  }

  DerivedType &
  operator =(const DerivedType &other)
  {
    BaseType::getDerived()->reset(other.take());

    return *this;
  }

protected:
  friend BaseType;
};

template <class T, class CleanupType = RPointerDeleter<T> >
class RScopedPointer
  : public RBasicScopedPointer<RScopedPointer<T, CleanupType>, T, CleanupType>
{
public:
  typedef RBasicScopedPointer<RScopedPointer<T, CleanupType>, T,
                              CleanupType> BaseType;
  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;

protected:
  // Don't allow create RScopedPointer without any argument!
  RScopedPointer();

public:
  RScopedPointer(T *ptr) : BaseType(ptr)
  {
  }

  RScopedPointer(DerivedType &other) : BaseType(other)
  {
  }
};

#endif // __INCLUDED_B9852640644F11E6878D00F1F38F93EF
