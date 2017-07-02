#ifndef __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C
#define __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C

#include "RGlobal.h"

class RCpuTimer
{
public:
  RCpuTimer();
  ~RCpuTimer();

  void
  start();
  void
  stop();
  /**
   * Calculate the interval between start() and this method.
   *
   * Unit in milliseconds.
   */
  uint32_t
  elapsed();

private:
  uint32_t mLastTime;
};

#endif /* __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C */
