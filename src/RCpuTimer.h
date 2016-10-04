#ifndef __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C
#define __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C

#include "RTypes.h"

class RCpuTimer
{
public:
  typedef TickType_t TimeType;

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
  TimeType
  elapsed();

  TickType_t
  elapsedTicks();

private:
  TickType_t mLastTime;
};

#endif /* __INCLUDED_BE81AF72390F11E5AA6EA088B4D1658C */
