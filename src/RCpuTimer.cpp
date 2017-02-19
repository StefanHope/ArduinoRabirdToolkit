#include "RCpuTimer.h"
#include <Arduino.h>

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
  mLastTime = xTaskGetTickCount();
}

void
RCpuTimer::stop()
{
}

rtime
RCpuTimer::elapsed()
{
  return elapsedTicks() * portTICK_PERIOD_MS;
}

rtime
RCpuTimer::elapsedTicks()
{
  rtime currentTime = xTaskGetTickCount();
  rtime elapsed     = 0;

  if(currentTime >= mLastTime)
  {
    elapsed = currentTime - mLastTime;
  }
  else
  {
    elapsed = portMAX_DELAY - mLastTime + currentTime;
  }

  return elapsed;
}
