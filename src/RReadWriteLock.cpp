#include "RReadWriteLock.h"
#include "RMutexLocker.h"
#include <limits>

RReadWriteLock::RReadWriteLock()
  : mReaders(0)
{
}

RReadWriteLock::~RReadWriteLock()
{
}

void
RReadWriteLock::lockForRead()
{
  R_MAKE_MUTEXLOCKER(&mReadMutex);

  if(mReaders == 0)
  {
    mWriteMutex.lock();
  }

  mReaders++;
}

void
RReadWriteLock::lockForWrite()
{
  mWriteMutex.lock();
}

bool
RReadWriteLock::tryLockForRead()
{
  return tryLockForRead(0);
}

bool
RReadWriteLock::tryLockForRead(int timeout)
{
  R_MAKE_MUTEXLOCKER(&mReadMutex);

  if(mReaders == 0)
  {
    if(!mWriteMutex.tryLock(timeout))
    {
      return false;
    }
  }

  mReaders++;
  return true;
}

bool
RReadWriteLock::tryLockForWrite()
{
  return tryLockForWrite(0);
}

bool
RReadWriteLock::tryLockForWrite(int timeout)
{
  return mWriteMutex.tryLock(timeout);
}

void
RReadWriteLock::unlock()
{
  R_MAKE_MUTEXLOCKER(&mReadMutex)

  if(mReaders > 0)
  {
    mReaders--;
  }

  if(mReaders == 0)
  {
    mWriteMutex.unlock();
  }
}
