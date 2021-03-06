#ifndef __INCLUDED_E4C4EA7CFFB111E6AA6EA088B4D1658C
#define __INCLUDED_E4C4EA7CFFB111E6AA6EA088B4D1658C

#include "RGlobal.h"
#include "RThread.h"

class RMutexRecursive
{
public:
  RMutexRecursive();
  ~RMutexRecursive();

  void
  lock();
  bool
  tryLock();
  bool
  tryLock(int timeout);
  void
  unlock();

private:
  rcount mCount;

  RThread::Id mThreadId;

  R_DISABLE_COPY(RMutexRecursive)
};

#endif // __INCLUDED_E4C4EA7CFFB111E6AA6EA088B4D1658C
