#ifndef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
#define __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF

#include "RBasicPointer.h"

template <class DerivedType_, class T>
class RBasicRawPointer
  : public RBasicPointer<DerivedType_, T, uintptr_t>
{
public:
  typedef RBasicPointer<DerivedType_, T, uintptr_t> BaseType;
  typedef typename BaseType::StorageType            StorageType;
  typedef typename BaseType::DerivedType            DerivedType;

public:
  RBasicRawPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RBasicRawPointer(const DerivedType &other) : BaseType(other)
  {
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

template <class T>
class RRawPointer
  : public RBasicRawPointer<RRawPointer<T>, T>
{
public:
  typedef RBasicRawPointer<RRawPointer<T>, T> BaseType;
  typedef typename BaseType::StorageType      StorageType;
  typedef typename BaseType::DerivedType      DerivedType;

public:
  RRawPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RRawPointer(const DerivedType &other) : BaseType(other)
  {
  }
};

#endif // #ifdef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
