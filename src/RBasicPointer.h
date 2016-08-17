#ifndef __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
#define __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF

#include <RTypes.h>

template <class DerivedType, class T, class StorageType = T *>
class RBasicPointer
{
public:
  typedef DerivedType ThisType;

  RBasicPointer() : mPtr(0)
  {
  }

  RBasicPointer(const ThisType &other) : mPtr(other.mPtr)
  {
  }

  ~RBasicPointer()
  {
    getThis()->clear();
  }

  T *
  data() const
  {
    return getThis()->fromStorageType(mPtr);
  }

  bool
  isNull() const
  {
    return (0 == getThis()->data());
  }

  void
  clear()
  {
    mPtr = 0;
  }

  void
  reset(T *ptr=0)
  {
    getThis()->clear();
    mPtr = getThis()->toStorageType(ptr);
  }

  void
  swap(ThisType &other)
  {
    ThisType temp;

    temp  = other;
    other = *this;
    *this = temp;
  }

  T *
  operator ->() const
  {
    return getThis()->data();
  }

  operator bool() const
  {
    return !getThis()->isNull();
  }

  bool
  operator !() const
  {
    return getThis()->isNull();
  }

  T &
  operator *() const
  {
    return *getThis()->data();
  }

  ThisType &
  operator =(const ThisType &other)
  {
    getThis()->reset(other.data());
    return *this;
  }

protected:
  inline
  StorageType
  toStorageType(const T *ptr)
  {
    return reinterpret_cast<StorageType>(ptr);
  }

  inline
  T *
  fromStorageType(StorageType ptr)
  {
    return reinterpret_cast<T *>(ptr);
  }

  inline
  DerivedType *
  getThis()
  {
    return static_cast<DerivedType *>(this);
  }

  inline
  const DerivedType *
  getThis() const
  {
    return static_cast<const DerivedType *>(this);
  }

private:
  StorageType mPtr;
};

#endif // __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
