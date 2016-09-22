#include "RMutexLocker.h"
#include "RMutex.h"

RMutexLocker::RMutexLocker(RMutex *mutex)
  : mMutex(mutex)
{
  if(mMutex)
  {
    mMutex->lock();
  }
}

RMutexLocker::~RMutexLocker()
{
  if(mMutex)
  {
    mMutex->unlock();
    mMutex = NULL;
  }
}
