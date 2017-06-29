#ifndef __INCLUDED_ABD23D008EF011E6AA6EA088B4D1658C
#define __INCLUDED_ABD23D008EF011E6AA6EA088B4D1658C

#include "RGlobal.h"

class RReadWriteLock;
class RReadLocker
{
public:
  RReadLocker(RReadWriteLock *lock);
  ~RReadLocker();

private:
  RReadWriteLock *mLock;

  R_DISABLE_COPY(RReadLocker)
};

#endif // __INCLUDED_ABD23D008EF011E6AA6EA088B4D1658C
