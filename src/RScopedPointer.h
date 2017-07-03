#ifndef __INCLUDED_B9852640644F11E6878D00F1F38F93EF
#define __INCLUDED_B9852640644F11E6878D00F1F38F93EF

#include "RUniquePointer.h"

template <class T, class CleanupType = RPointerDeleter<T> >
class RScopedPointer
  : public RBasicUniquePointer<RScopedPointer<T, CleanupType>, T, CleanupType>
{
public:
  typedef RBasicUniquePointer<RScopedPointer<T, CleanupType>, T,
                              CleanupType> BaseType;
  typedef typename BaseType::StorageType StorageType;
  typedef typename BaseType::DerivedType DerivedType;

protected:
  // Don't allow create RScopedPointer without any argument!
  explicit
  RScopedPointer();

public:
  explicit RScopedPointer(T *ptr) : BaseType(ptr)
  {
  }

private:
  R_DISABLE_COPY(RScopedPointer);
  R_DISABLE_NEW(RScopedPointer);
};

#endif // __INCLUDED_B9852640644F11E6878D00F1F38F93EF
