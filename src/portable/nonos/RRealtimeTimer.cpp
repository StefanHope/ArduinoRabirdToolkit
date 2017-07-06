#include <RGlobal.h>

#ifdef R_OS_NONOS

#include "RRealtimeTimer.h"
#include "RScopedPointer.h"
#include "RIsr.h"
#include "RThread.h"
#include "REventLoop.h"

RRealtimeTimer::RRealtimeTimer()
  : mIsSingleShot(false)
  , mIsActive(false)
{
  mIt = thread()->eventLoop()->mTimerQueue.end();
}

RRealtimeTimer::~RRealtimeTimer()
{
}

int32_t
RRealtimeTimer::interval() const
{
  return mInterval;
}

bool
RRealtimeTimer::isActive() const
{
  return mIsActive;
}

bool
RRealtimeTimer::isSingleShot() const
{
  return mIsSingleShot;
}

void
RRealtimeTimer::setInterval(int32_t msec)
{
  mInterval = msec;
}

void
RRealtimeTimer::setSingleShot(bool singleShot)
{
  mIsSingleShot = singleShot;
}

int
RRealtimeTimer::timerId() const
{
  // WARNING: We shorten handle to id value, but it may lead duplicate id values.
  return rShortenPtr(this);
}

void
RRealtimeTimer::start()
{
  thread()->eventLoop()->startTimer(this);
  mIsActive = true;
}

void
RRealtimeTimer::start(int32_t msec)
{
  setInterval(msec);
  start();
}

void
RRealtimeTimer::stop()
{
  mIsActive = false;
  thread()->eventLoop()->stopTimer(this);
}

void
RRealtimeTimer::run()
{
}

bool
RRealtimeTimer::_isRestartFromCallback()
{
  return true;
}

void
RRealtimeTimer::_redirectEvents()
{
}

#endif // #ifdef R_OS_NONOS
