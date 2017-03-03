#include "RSemaphore.h"
#include "RSpinLocker.h"
#include "RThread.h"

RSemaphore::RSemaphore(rcount n)
  : mCount(n)
{
}

RSemaphore::~RSemaphore()
{
}

void
RSemaphore::acquire(rcount n)
{
  tryAcquire(n, -1);
}

rcount
RSemaphore::available() const
{
  R_MAKE_SPINLOCKER();
  return mCount;
}

void
RSemaphore::release(rcount n)
{
  R_MAKE_SPINLOCKER();

  mCount += n;
}

bool
RSemaphore::tryAcquire(rcount n)
{
  return tryAcquire(n, 0);
}

bool
RSemaphore::tryAcquire(rcount n, int ms)
{
  while(1)
  {
    {
      R_MAKE_SPINLOCKER();

      if(mCount >= n)
      {
        mCount -= n;
        return true;
      }
    }

    if(ms < 0)
    {
      // Loop infinite ...
    }
    else if(ms < portTICK_PERIOD_MS)
    {
      return false;
    }
    else
    {
      ms -= portTICK_PERIOD_MS;
    }

    RThread::yieldCurrentThread();
  }
}
