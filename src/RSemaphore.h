#ifndef __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C
#define __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C

#include "RTypes.h"

class RSemaphore
{
public:
  RSemaphore(rcount n=0);
  ~RSemaphore();

  void
  acquire(rcount n=1);

  int
  available() const;

  void
  release(rcount n=1);

  bool
  tryAcquire(rcount n=1);

  bool
  tryAcquire(rcount n, int ms);

private:
  SemaphoreHandle_t mHandle;

  R_DISABLE_COPY(RSemaphore)
};

#endif // __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C
