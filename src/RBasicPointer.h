#ifndef __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
#define __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF

#include <RTypes.h>

template <class DerivedType_, class T, class StorageType_ = T *>
class RBasicPointer
{
public:
  typedef DerivedType_ DerivedType;
  typedef T            ValueType;
  typedef StorageType_ StorageType;

  RBasicPointer() : mPtr(0)
  {
  }

  RBasicPointer(const T *ptr) : mPtr(0)
  {
    getDerived()->reset(ptr);
  }

  RBasicPointer(const DerivedType &other) : mPtr(other.mPtr)
  {
  }

  ~RBasicPointer()
  {
    getDerived()->clear();
  }

  T *
  data() const
  {
    return getDerived()->fromStorageType(mPtr);
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
  reset(T *ptr=0)
  {
    getDerived()->clear();
    mPtr = getDerived()->toStorageType(ptr);
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

  DerivedType &
  operator =(const DerivedType &other)
  {
    getDerived()->reset(other.data());
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
  getDerived()
  {
    return static_cast<DerivedType *>(this);
  }

  inline
  const DerivedType *
  getDerived() const
  {
    return static_cast<const DerivedType *>(this);
  }

private:
  StorageType mPtr;
};

#endif // __INCLUDED_DFE14DD2645911E6BAE000F1F38F93EF
