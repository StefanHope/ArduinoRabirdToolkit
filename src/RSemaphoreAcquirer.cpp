#include "RSemaphoreAcquirer.h"
#include "RSemaphore.h"

RSemaphoreAcquirer::RSemaphoreAcquirer(RSemaphore *semaphore, rcount n)
  : mSemaphore(semaphore), mCount(n)
{
  if(mSemaphore && (mCount > 0))
  {
    mSemaphore->acquire(mCount);
  }
}

RSemaphoreAcquirer::~RSemaphoreAcquirer()
{
  if(mSemaphore && (mCount > 0))
  {
    mSemaphore->release(mCount);
  }
}
