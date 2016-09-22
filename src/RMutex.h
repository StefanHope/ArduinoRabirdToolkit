#ifndef __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C
#define __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C

#include "RTypes.h"
#include <semphr.h>

class RMutex
{
public:
  enum RecursionMode
  {
    NonRecursive,
    Recursive,
  };

public:
  RMutex(RecursionMode mode=NonRecursive);
  ~RMutex();

  void
  lock();
  bool
  tryLock();
  bool
  tryLock(int timeout);
  void
  unlock();

private:
  RecursionMode     mMode;
  SemaphoreHandle_t mHandle;

  R_DISABLE_COPY(RMutex)
};

#endif // __INCLUDED_3ACAB96A807D11E6AA6EA088B4D1658C
