#include "RSemaphoreAcquirer.h"
#include "RSemaphore.h"

RSemaphoreAcquirer::RSemaphoreAcquirer(RSemaphore *semaphore, int n)
  : mSemaphore(semaphore), mCount(n)
{
  if(mSemaphore)
  {
    mSemaphore->acquire(mCount);
  }
}

RSemaphoreAcquirer::~RSemaphoreAcquirer()
{
  if(mSemaphore)
  {
    mSemaphore->release(mCount);
  }
}
