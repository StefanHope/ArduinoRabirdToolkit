#include "RTimer.h"
#include "RTimerEvent.h"
#include "RCoreApplication.h"
#include "RScopedPointer.h"
#include "RIsr.h"
#include "RThread.h"

RTimer::RTimer()
  : mHandle(NULL)
  , mIsSingleShot(false)
  , mExtended(0)
#if defined(configUSE_16_BIT_TICKS) && (configUSE_16_BIT_TICKS == 1)
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
    onTimeout
    );
  vTimerSetTimerID(mHandle, this);
}

RTimer::~RTimer()
{
  while(pdPASS != xTimerDelete(mHandle, portMAX_DELAY))
  {
    RThread::yieldCurrentThread();
  }
}

int32_t
RTimer::interval() const
{
  return xTimerGetPeriod(mHandle) * portTICK_PERIOD_MS
#if defined(configUSE_16_BIT_TICKS) && (configUSE_16_BIT_TICKS == 1)
         + mExtended * portMAX_DELAY;
#endif
  ;
}

bool
RTimer::isActive() const
{
  return xTimerIsTimerActive(mHandle);
}

bool
RTimer::isSingleShot() const
{
  return mIsSingleShot;
}

void
RTimer::setInterval(int32_t msec)
{
  static const int32_t blockMS = static_cast<int32_t>(portMAX_DELAY) *
                                 portTICK_PERIOD_MS;

#if defined(configUSE_16_BIT_TICKS) && (configUSE_16_BIT_TICKS == 1)
  mExtended = msec / blockMS;
  msec      = msec % blockMS;
#endif

  msec /= portTICK_PERIOD_MS;

  if(msec <= 0)
  {
    msec = 1;
  }

  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerChangePeriodFromISR(mHandle, msec, &xHigherPriorityTaskWoken);
  }
  else
  {
    while(pdPASS != xTimerChangePeriod(mHandle, msec, portMAX_DELAY))
    {
      RThread::yieldCurrentThread();
    }
  }

  // xTimerChangePeriod will cause timer start, so we need to stop it
  // immediately
  stop();
}

void
RTimer::setSingleShot(bool singleShot)
{
  mIsSingleShot = singleShot;
}

int
RTimer::timerId() const
{
  // WARNING: We shorten handle to id value, but it may lead duplicate id values.
  return rShortenPtr(pvTimerGetTimerID(mHandle));
}

void
RTimer::start()
{
  start(interval());
}

void
RTimer::start(int32_t msec)
{
  setInterval(msec);

#if defined(configUSE_16_BIT_TICKS) && (configUSE_16_BIT_TICKS == 1)
  mExtendedCounter = mExtended;
#endif

  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStartFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else
  {
    while(pdPASS != xTimerStart(mHandle, portMAX_DELAY))
    {
      RThread::yieldCurrentThread();
    }
  }
}

void
RTimer::stop()
{
  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStopFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else
  {
    while(pdPASS != xTimerStop(mHandle, portMAX_DELAY))
    {
      RThread::yieldCurrentThread();
    }
  }
}

bool
RTimer::event(REvent *e)
{
  if(e->type() == RTimerEvent::staticType())
  {
    // FIXME: Here may be generate a potential crash
    auto timerEvent = static_cast<RTimerEvent *>(e);

    timeout.emit();

    if(!mIsSingleShot)
    {
      start(); // Restart timer for next round
    }

    timerEvent->accept();
    return true;
  }

  return RObject::event(e);
}

void
RTimer::onTimeout(TimerHandle_t handle)
{
  auto self = static_cast<RTimer *>(pvTimerGetTimerID(handle));

#if defined(configUSE_16_BIT_TICKS) && (configUSE_16_BIT_TICKS == 1)

  if(self->mExtendedCounter > 0)
  {
    --self->mExtendedCounter;

    if(_rIsrExecuting())
    {
      BaseType_t xHigherPriorityTaskWoken = pdFALSE;

      xTimerChangePeriodFromISR(
        self->mHandle, portMAX_DELAY, &xHigherPriorityTaskWoken);
    }
    else
    {
      while(pdPASS !=
            xTimerChangePeriod(self->mHandle, portMAX_DELAY, portMAX_DELAY))
      {
        RThread::yieldCurrentThread();
      }
    }

    return;
  }

#endif

  // NOTE: Event will be deleted in REventLoop after they handled that event.
  RScopedPointer<RTimerEvent> event(new RTimerEvent(self->timerId()));

  RCoreApplication::postEvent(self, event.take());
}
