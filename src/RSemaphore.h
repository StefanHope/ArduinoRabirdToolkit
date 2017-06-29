#ifndef __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C
#define __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C

#include "RGlobal.h"

class RSemaphore
{
public:
  RSemaphore(rcount n=0);
  ~RSemaphore();

  void
  acquire(rcount n=1);

  rcount
  available() const;

  void
  release(rcount n=1);

  bool
  tryAcquire(rcount n=1);

  bool
  tryAcquire(rcount n, int ms);

private:
  rcount mCount;

  R_DISABLE_COPY(RSemaphore)
};

#endif // __INCLUDED_8429D54C812B11E6AA6EA088B4D1658C
