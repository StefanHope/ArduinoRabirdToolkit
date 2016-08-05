#ifndef __INCLUDED_C140043A425411E6A04700F1F38F93EF
#define __INCLUDED_C140043A425411E6A04700F1F38F93EF

#include <stdint.h>

template <class Type>
inline
uintptr_t
rShortenPtr(const Type * longPtr)
{
  return static_cast<uintptr_t>(reinterpret_cast<int>(const_cast<Type *>(longPtr)));
}

template <class PtrType>
inline
PtrType
rLengthenPtr(uintptr_t shortPtr)
{
  return reinterpret_cast<PtrType>(static_cast<int>((shortPtr)));
}

/**
 * Calculate how much elements in the array
 *
 * @param array Target array variant to calculate
 */
#define R_SIZE_OF_ARRAY(array) (sizeof((array))/sizeof((array)[0]))

/**
 * Disable copy constructor and assign operations.
 *
 */
#define R_DISABLE_COPY(Class) \
  Class(const Class &); \
  Class &operator=(const Class &);

#endif // __INCLUDED_C140043A425411E6A04700F1F38F93EF
