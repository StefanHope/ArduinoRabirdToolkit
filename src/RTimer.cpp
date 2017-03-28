#include "RTimer.h"
#include "RTimerEvent.h"
#include "RCoreApplication.h"
#include "RScopedPointer.h"
#include "RIsr.h"
#include "RThread.h"

static const int32_t sMaxDelayMS = static_cast<int32_t>(portMAX_DELAY) *
                                   portTICK_PERIOD_MS;

RTimer::RTimer()
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
  return static_cast<int32_t>(xTimerGetPeriod(mHandle)) * portTICK_PERIOD_MS
#if (configUSE_16_BIT_TICKS == 1)
         * (mExtended + 1)
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
  else
  {
    taskENTER_CRITICAL();

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerChangePeriodFromISR(mHandle, static_cast<rtime>(msec),
                              &xHigherPriorityTaskWoken);

    // xTimerChangePeriod will cause timer start, so we need to stop it
    // immediately
    xHigherPriorityTaskWoken = pdFALSE;
    xTimerStopFromISR(mHandle, &xHigherPriorityTaskWoken);

    taskEXIT_CRITICAL();
  }
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
#if (configUSE_16_BIT_TICKS == 1)
  mExtendedCounter.store(mExtended);
#endif

  if(_rIsrExecuting())
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStartFromISR(mHandle, &xHigherPriorityTaskWoken);
  }
  else
  {
    taskENTER_CRITICAL();

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStartFromISR(mHandle, &xHigherPriorityTaskWoken);

    taskEXIT_CRITICAL();
  }
}

void
RTimer::start(int32_t msec)
{
  setInterval(msec);
  start();
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
    taskENTER_CRITICAL();

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xTimerStopFromISR(mHandle, &xHigherPriorityTaskWoken);

    taskEXIT_CRITICAL();
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

#if (configUSE_16_BIT_TICKS == 1)

  if(self->mExtendedCounter.addIfLargeThan(0, -1))
  {
    if(_rIsrExecuting())
    {
      BaseType_t xHigherPriorityTaskWoken = pdFALSE;

      xTimerStartFromISR(
        self->mHandle, &xHigherPriorityTaskWoken);
    }
    else
    {
      taskENTER_CRITICAL();

      BaseType_t xHigherPriorityTaskWoken = pdFALSE;

      xTimerStartFromISR(self->mHandle, &xHigherPriorityTaskWoken);

      taskEXIT_CRITICAL();
    }

    return;
  }

#endif

  // NOTE: Event will be deleted in REventLoop after they handled that event.
  RScopedPointer<RTimerEvent> event(new RTimerEvent(self->timerId()));

  RCoreApplication::postEvent(self, event.take());
}
