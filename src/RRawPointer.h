#ifndef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
#define __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF

#include "RPointer.h"

template <class T>
class RPointerDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    delete ptr;
  }
};

template <class T>
class RPointerPodDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    free(ptr);
  }
};

template <class T>
class RPointerArrayDeleter
{
public:
  static void
  cleanup(T *ptr)
  {
    delete[] ptr;
  }
};

template <class DerivedType_, class T>
class RBasicRawPointer
  : public RBasicPointer<DerivedType_, T, uintptr_t>
{
public:
  typedef RBasicPointer<DerivedType_, T, uintptr_t> BaseType;

  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;

public:
  RBasicRawPointer() : BaseType()
  {
  }

  RBasicRawPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RBasicRawPointer(const DerivedType &other) : BaseType(other)
  {
  }

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
};

template <class T>
class RRawPointer
  : public RBasicRawPointer<RRawPointer<T>, T>
{
public:
  typedef RBasicRawPointer<RRawPointer<T>, T> BaseType;

  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;

public:
  RRawPointer() : BaseType()
  {
  }

  RRawPointer(const T *ptr) : BaseType(ptr)
  {
  }

  RRawPointer(const DerivedType &other) : BaseType(other)
  {
  }
};

#endif // #ifdef __INCLUDED_B0C76BDC59FD11E6BE6F00F1F38F93EF
