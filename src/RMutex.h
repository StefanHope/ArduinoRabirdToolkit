#ifndef __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C
#define __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C

#include "RGlobal.h"

class RThread;
class RMutex
{
public:
  RMutex();
  ~RMutex();

  void
  lock();
  bool
  tryLock();
  bool
  tryLock(int timeout);
  void
  unlock();

private:
  bool mIsLocked;

  R_DISABLE_COPY(RMutex)
};

#endif // __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C
