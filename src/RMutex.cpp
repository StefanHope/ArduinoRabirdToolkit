#include "RMutex.h"
#include "RThread.h"
#include "RSpinLocker.h"

RMutex::RMutex()
  : mIsLocked(false)
{
}

RMutex::~RMutex()
{
}

void
RMutex::lock()
{
  // INCLUDE_vTaskSuspend should specific to 1 for infinite loop !
  tryLock(-1);
}

bool
RMutex::tryLock()
{
  return tryLock(0);
}

bool
RMutex::tryLock(int timeout)
{
  while(1)
  {
    {
      R_MAKE_SPINLOCKER();

      if(!mIsLocked)
      {
        mIsLocked = true;
        return true;
      }
    }

    if(timeout < 0)
    {
      // Loop infinite ...
    }
    else if(timeout < RPORT_TICK_PERIOD_MS)
    {
      return false;
    }
    else
    {
      timeout -= RPORT_TICK_PERIOD_MS;
    }

    RThread::yieldCurrentThread();
  }
}

void
RMutex::unlock()
{
  R_MAKE_SPINLOCKER();

  mIsLocked = false;
}
