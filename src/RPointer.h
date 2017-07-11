#ifndef __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
#define __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF

#include "RGlobal.h"

template <class DerivedType_, class T, class StorageType_ = T *>
class RBasicPointer
{
public:
  typedef DerivedType_                                       DerivedType;
  typedef T                                                  ValueType;
  typedef StorageType_                                       StorageType;
  typedef RBasicPointer<DerivedType, ValueType, StorageType> ThisType;

  explicit RBasicPointer() : mPtr(0)
  {
  }

  explicit RBasicPointer(const T *ptr) : mPtr(getDerived()->toStorageType(ptr))
  {
  }

  explicit RBasicPointer(const DerivedType &other) : mPtr(other.mPtr)
  {
  }

  ~RBasicPointer()
  {
    getDerived()->clear();
  }

  T *
  data() const
  {
    return const_cast<T *>(const_cast<DerivedType *>(getDerived())->
                            fromStorageType(mPtr));
  }

  bool
  isNull() const
  {
    return (0 == getDerived()->data());
  }

  void
  clear()
  {
    mPtr = 0;
  }

  void
  reset(const T *ptr=0)
  {
    getDerived()->clear();
    rawReset(ptr);
  }

  void
  swap(DerivedType &other)
  {
    DerivedType temp;

    temp  = other;
    other = *this;
    *this = temp;
  }

  T *
  operator ->() const
  {
    return getDerived()->data();
  }

  operator bool() const
  {
    return !getDerived()->isNull();
  }

  bool
  operator !() const
  {
    return getDerived()->isNull();
  }

  T &
  operator *() const
  {
    return *getDerived()->data();
  }

  template <class OtherType>
  bool
  operator ==(const OtherType *ptr) const
  {
    return getDerived()->data() == ptr;
  }

  template <class OtherType>
  bool
  operator !=(const OtherType *ptr) const
  {
    return getDerived()->data() != ptr;
  }

  DerivedType &
  operator =(const DerivedType &other)
  {
    getDerived()->reset(other.data());
    return *this;
  }

  inline
  const StorageType
  toStorageType(const T *ptr) const
  {
    return reinterpret_cast<const StorageType>(ptr);
  }

  inline
  T *
  fromStorageType(StorageType ptr) const
  {
    return reinterpret_cast<T *>(ptr);
  }

protected:
  void
  rawReset(const T *ptr=0) const
  {
    mPtr = const_cast<DerivedType *>(getDerived())->toStorageType(ptr);
  }

  inline
  DerivedType *
  getDerived()
  {
    return static_cast<DerivedType *>(const_cast<ThisType *>(this));
  }

  inline
  const DerivedType *
  getDerived() const
  {
    return static_cast<DerivedType *>(const_cast<ThisType *>(this));
  }

  StorageType &
  internalStorage() const
  {
    return mPtr;
  }

private:
  mutable StorageType mPtr;
};

#endif // __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
