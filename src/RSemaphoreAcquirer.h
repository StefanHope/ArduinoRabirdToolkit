#ifndef __INCLUDED_3C64FD98814111E6AA6EA088B4D1658C
#define __INCLUDED_3C64FD98814111E6AA6EA088B4D1658C

#include "RGlobal.h"

class RSemaphore;
class RSemaphoreAcquirer
{
public:
  RSemaphoreAcquirer(RSemaphore *semaphore, rcount n=1);
  ~RSemaphoreAcquirer();

private:
  RSemaphore *mSemaphore;
  rcount      mCount;

  R_DISABLE_COPY(RSemaphoreAcquirer)
};

#endif // __INCLUDED_3C64FD98814111E6AA6EA088B4D1658C
