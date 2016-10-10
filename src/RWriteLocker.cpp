#include "RWriteLocker.h"
#include "RReadWriteLock.h"

RWriteLocker::RWriteLocker(RReadWriteLock *lock)
  : mLock(lock)
{
  if(mLock)
  {
    mLock->lockForWrite();
  }
}

RWriteLocker::~RWriteLocker()
{
  if(mLock)
  {
    mLock->unlock();
    mLock = NULL;
  }
}
