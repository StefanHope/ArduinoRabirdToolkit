#include "RRealtimeTimer.h"
#include "RScopedPointer.h"
#include "RIsr.h"
#include "RThread.h"

#define RREALTIME_TIMER_WAIT_PASS(code) \
  while(pdPASS != (code)) \
  { \
    RThread::yieldCurrentThread(); \
  }

static const int32_t sMaxDelayMS = static_cast<int32_t>(portMAX_DELAY) *
                                   portTICK_PERIOD_MS;

RRealtimeTimer::RRealtimeTimer()
  : mHandle(NULL)
  , mIsSingleShot(false)
  , mExtended(0)
#if (configUSE_16_BIT_TICKS == 1)
  , mExtendedCounter(0)
#endif
{
  // NOTE: Set timer run as idle task by default, but we can't set interval to
  // zero, otherwise the created timer will return to NULL, so we give value 1 .
  mHandle = xTimerCreate(
    "",
    1,
    pdFALSE,                           // one-shot timer
    reinterpret_cast<void *>(0),
    _callback
    );

  vTimerSetTimerID(mHandle, this);
}

RRealtimeTimer::~RRealtimeTimer()
{
  RREALTIME_TIMER_WAIT_PASS(xTimerDelete(mHandle, portMAX_DELAY));
}

int32_t
RRealtimeTimer::interval() const
{
  return static_cast<int32_t>(xTimerGetPeriod(mHandle)) * portTICK_PERIOD_MS
#if (configUSE_16_BIT_TICKS == 1)
         * (mExtended + 1)
#endif
  ;
}

bool
RRealtimeTimer::isActive() const
{
  return xTimerIsTimerActive(mHandle);
}

bool
RRealtimeTimer::isSingleShot() const
{
  return mIsSingleShot;
}

void
RRealtimeTimer::setInterval(int32_t msec)
{
#if (configUSE_16_BIT_TICKS == 1)
  mExtended = static_cast<uint8_t>(msec / sMaxDelayMS);

  // A little trick to generate a fixed delay value, so that we needs not to
  // store the remainder
  msec /= (mExtended + 1);
#endif

  msec /= portTICK_PERIOD_MS;

  if(msec <= 0)
  {
    msec = 1;
  }

  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerChangePeriodFromISR(mHandle, static_cast<rtime>(msec),
                              &xHigherPriorityTaskWoken);

    // xTimerChangePeriod will cause timer start, so we need to stop it
    // immediately
    xHigherPriorityTaskWoken = pdFALSE;
    xTimerStopFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else if(RThread::currentThreadId() == xTimerGetTimerDaemonTaskHandle())
  {
    xTimerChangePeriod(mHandle, static_cast<rtime>(msec), 0);
    xTimerStop(mHandle, 0);
  }
  else
  {
    RREALTIME_TIMER_WAIT_PASS(xTimerChangePeriod(
                                mHandle, static_cast<rtime>(msec),
                                portMAX_DELAY));
    RREALTIME_TIMER_WAIT_PASS(xTimerStop(mHandle, portMAX_DELAY));
  }
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
  return rShortenPtr(pvTimerGetTimerID(mHandle));
}

void
RRealtimeTimer::start()
{
#if (configUSE_16_BIT_TICKS == 1)
  mExtendedCounter.store(mExtended);
#endif

  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStartFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else if(RThread::currentThreadId() == xTimerGetTimerDaemonTaskHandle())
  {
    xTimerStart(mHandle, 0);
  }
  else
  {
    RREALTIME_TIMER_WAIT_PASS(xTimerStart(mHandle, portMAX_DELAY));
  }
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
  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStopFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else if(RThread::currentThreadId() == xTimerGetTimerDaemonTaskHandle())
  {
    xTimerStop(mHandle, 0);
  }
  else
  {
    RREALTIME_TIMER_WAIT_PASS(xTimerStop(mHandle, portMAX_DELAY));
  }
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

void
RRealtimeTimer::_callback(TimerHandle_t handle)
{
  auto self = static_cast<RRealtimeTimer *>(pvTimerGetTimerID(handle));

#if (configUSE_16_BIT_TICKS == 1)

  if(self->mExtendedCounter.addIfLargeThan(0, -1))
  {
    // Do not use a block time if calling a timer API function from a
    // timer callback function, as doing so could cause a deadlock!
    xTimerStart(self->mHandle, 0);
    return;
  }

#endif

  if(self->_isRestartFromCallback())
  {
    // Do restart action inside event loop
    self->_redirectEvents();
    return;
  }
  else
  {
    self->run();
  }

  if(self->isSingleShot())
  {
    return;
  }

  xTimerStart(self->mHandle, 0);
}
