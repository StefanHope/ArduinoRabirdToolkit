#ifndef __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C
#define __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C

#include "RTypes.h"

class RMutex;
class RMutexLocker
{
public:
  RMutexLocker(RMutex *mutex);
  ~RMutexLocker();

private:
  RMutex *mMutex;
};

#endif // __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C
