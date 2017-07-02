#include "RCpuTimer.h"

RCpuTimer::RCpuTimer() :
  mLastTime(0)
{
}

RCpuTimer::~RCpuTimer()
{
}

void
RCpuTimer::start()
{
  mLastTime = millis();
}

void
RCpuTimer::stop()
{
}

uint32_t
RCpuTimer::elapsed()
{
  return millis() - mLastTime;
}
