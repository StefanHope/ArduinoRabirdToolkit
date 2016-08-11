#ifndef __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
#define __INCLUDED_288D29285F8911E68BCF00F1F38F93EF

#include "RTypes.h"

/**
 * A simple class to wrap around the interrupt disable/enable pairs.
 *
 * @brief The RSpinLock class
 */
class RSpinLock
{
public:
  RSpinLock();
  ~RSpinLock();

private:
  R_DISABLE_COPY(RSpinLock);
};

#endif // __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
