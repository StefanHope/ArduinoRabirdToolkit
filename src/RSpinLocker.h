#ifndef __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
#define __INCLUDED_288D29285F8911E68BCF00F1F38F93EF

#include "RTypes.h"

/**
 * A simple class to wrap around the interrupt disable/enable pairs.
 */
class RSpinLocker
{
public:
  RSpinLocker();
  ~RSpinLocker();

private:
  uint8_t mOldRegisters;

private:
  R_DISABLE_COPY(RSpinLocker)
};

#define _R_MAKE_SPINLOCKER(lineNumber) \
  RSpinLocker __rTempSpinLocker##lineNumber;

#define R_MAKE_SPINLOCKER() _R_MAKE_SPINLOCKER(__LINE__)

#endif // __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
