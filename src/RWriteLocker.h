#ifndef __INCLUDED_F0E182168EF011E6AA6EA088B4D1658C
#define __INCLUDED_F0E182168EF011E6AA6EA088B4D1658C

#include "RTypes.h"

class RReadWriteLock;
class RWriteLocker
{
public:
  RWriteLocker(RReadWriteLock *lock);
  ~RWriteLocker();

private:
  RReadWriteLock *mLock;

  R_DISABLE_COPY(RWriteLocker)
};

#endif // __INCLUDED_F0E182168EF011E6AA6EA088B4D1658C
