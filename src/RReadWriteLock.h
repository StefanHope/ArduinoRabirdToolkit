#ifndef __INCLUDED_8DDD46248A7111E6AA6EA088B4D1658C
#define __INCLUDED_8DDD46248A7111E6AA6EA088B4D1658C

#include <RMutex.h>

class RReadWriteLock
{
public:
  enum RecursionMode
  {
    NonRecursive,
    Recursive,
  };

public:
  RReadWriteLock(RecursionMode mode=NonRecursive);
  ~RReadWriteLock();

  void
  lockForRead();
  void
  lockForWrite();
  bool
  tryLockForRead();
  bool
  tryLockForRead(int timeout);
  bool
  tryLockForWrite();
  bool
  tryLockForWrite(int timeout);
  void
  unlock();

private:
  RMutex mReadMutex;
  RMutex mWriteMutex;
  rcount mReaders;

  R_DISABLE_COPY(RReadWriteLock)
};

#endif // __INCLUDED_8DDD46248A7111E6AA6EA088B4D1658C
