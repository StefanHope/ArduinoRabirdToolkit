#ifndef __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
#define __INCLUDED_288D29285F8911E68BCF00F1F38F93EF

#include "RGlobal.h"

/**
 * A simple class to wrap around the FreeRTOS suspend/resume pairs.
 *
 * To ensure code statements safe to work between threads (FreeRTOS tasks).
 */
class RSpinLocker
{
public:
  RSpinLocker();
  ~RSpinLocker();

private:
  R_DISABLE_COPY(RSpinLocker)
};

#define _R_MAKE_SPINLOCKER(lineNumber) \
  RSpinLocker __rTempSpinLocker##lineNumber;

#define R_MAKE_SPINLOCKER() _R_MAKE_SPINLOCKER(__LINE__)

#endif // __INCLUDED_288D29285F8911E68BCF00F1F38F93EF
