#include "RMutexRecursive.h"
#include "RThread.h"
#include "RSpinLocker.h"

RMutexRecursive::RMutexRecursive()
  : mCount(0), mThreadId(0)
{
}

RMutexRecursive::~RMutexRecursive()
{
}

void
RMutexRecursive::lock()
{
  // INCLUDE_vTaskSuspend should specific to 1 for infinite loop !
  tryLock(-1);
}

bool
RMutexRecursive::tryLock()
{
  return tryLock(0);
}

bool
RMutexRecursive::tryLock(int timeout)
{
  auto currentThreadId = RThread::currentThreadId();

  while(1)
  {
    {
      R_MAKE_SPINLOCKER();

      if((0 == mThreadId) || (currentThreadId == mThreadId))
      {
        ++mCount;
        mThreadId = currentThreadId;
        return true;
      }
    }

    if(timeout < 0)
    {
      // Loop infinite ...
    }
    else if(timeout < portTICK_PERIOD_MS)
    {
      return false;
    }
    else
    {
      timeout -= portTICK_PERIOD_MS;
    }

    RThread::yieldCurrentThread();
  }
}

void
RMutexRecursive::unlock()
{
  R_MAKE_SPINLOCKER();

  if(RThread::currentThreadId() == mThreadId)
  {
    --mCount;

    if(0 == mCount)
    {
      mThreadId = 0;
    }
  }
}
