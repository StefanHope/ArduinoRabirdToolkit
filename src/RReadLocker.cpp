#include "RReadLocker.h"
#include "RReadWriteLock.h"

RReadLocker::RReadLocker(RReadWriteLock *lock)
  : mLock(lock)
{
  if(mLock)
  {
    mLock->lockForRead();
  }
}

RReadLocker::~RReadLocker()
{
  if(mLock)
  {
    mLock->unlock();
    mLock = NULL;
  }
}
