#include "RTimer.h"
#include "RTimerEvent.h"
#include "RCoreApplication.h"
#include "RScopedPointer.h"

RTimer::RTimer() : mIsSingleShot(false)
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
  xTimerDelete(mHandle, 0);
}

int
RTimer::interval() const
{
  return xTimerGetPeriod(mHandle) * portTICK_PERIOD_MS;
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
RTimer::setInterval(int msec)
{
  msec /= portTICK_PERIOD_MS;

  if(msec <= 0)
  {
    msec = 1;
  }

  xTimerChangePeriod(mHandle, msec, 0);

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
RTimer::start(int msec)
{
  setInterval(msec);
  start();
}

void
RTimer::start()
{
  stop();
  xTimerStart(mHandle, 0);
}

void
RTimer::stop()
{
  xTimerStop(mHandle, 0);
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

  // NOTE: Event will be deleted in REventLoop after they handled that event.
  RScopedPointer<RTimerEvent> event(new RTimerEvent(self->timerId()));

  RCoreApplication::postEvent(self, event.take());
}
