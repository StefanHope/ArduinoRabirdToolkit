#ifndef __INCLUDED_29956D7603E411E7AA6EA088B4D1658C
#define __INCLUDED_29956D7603E411E7AA6EA088B4D1658C

#include "RRawPointer.h"

template <class DerivedType_, class T, class CleanupType>
class RBasicUniquePointer
  : public RBasicRawPointer<DerivedType_, T>
{
public:
  typedef RBasicRawPointer<DerivedType_, T> BaseType;
  typedef typename BaseType::StorageType    StorageType;
  typedef typename BaseType::DerivedType    DerivedType;

public:
  explicit RBasicUniquePointer() : BaseType()
  {
  }

  explicit RBasicUniquePointer(T *ptr) : BaseType(ptr)
  {
  }

  ~RBasicUniquePointer()
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
    T *ptr = BaseType::getDerived()->data();

    // WARNING: Only clear the ptr, don't delete it!
    BaseType::clear();

    return ptr;
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
class RUniquePointer
  : public RBasicUniquePointer<RUniquePointer<T, CleanupType>, T, CleanupType>
{
public:
  typedef RBasicUniquePointer<RUniquePointer<T, CleanupType>, T,
                              CleanupType> BaseType;
  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;

public:
  explicit RUniquePointer() : BaseType()
  {
  }

  explicit RUniquePointer(T *ptr) : BaseType(ptr)
  {
  }
};

#endif // __INCLUDED_29956D7603E411E7AA6EA088B4D1658C
