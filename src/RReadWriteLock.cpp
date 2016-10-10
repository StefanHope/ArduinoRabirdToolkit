#include "RReadWriteLock.h"
#include "RMutexLocker.h"
#include <limits>

RReadWriteLock::RReadWriteLock(RReadWriteLock::RecursionMode mode)
  : mReadMutex()
  , mWriteMutex((mode ==
                 NonRecursive) ? RMutex::NonRecursive : RMutex::Recursive)
  , mReaders(0)
{
}

RReadWriteLock::~RReadWriteLock()
{
}

void
RReadWriteLock::lockForRead()
{
  RMutexLocker readLocker(&mReadMutex);

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
  RMutexLocker readLocker(&mReadMutex);

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
  RMutexLocker readLocker(&mReadMutex);

  if(mReaders > 0)
  {
    mReaders--;
  }

  if(mReaders == 0)
  {
    mWriteMutex.unlock();
  }
}
