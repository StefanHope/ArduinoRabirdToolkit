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

RCpuTimer::TimeType
RCpuTimer::elapsed()
{
  return elapsedTicks() * portTICK_PERIOD_MS;
}

TickType_t
RCpuTimer::elapsedTicks()
{
  TickType_t currentTime = xTaskGetTickCount();
  TickType_t elapsed     = 0;

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
