#include "RTimer.h"
#include "RTimerEvent.h"
#include "RCoreApplication.h"
#include "RScopedPointer.h"

RTimer::RTimer()
  : mIsSingleShot(false)
  , mInterval(0)
  , mHandle(0)
{
}

RTimer::~RTimer()
{
  if(mHandle)
  {
    xTimerDelete(mHandle, 0);
    mHandle = 0;
  }
}

int
RTimer::interval() const
{
  return mInterval;
}

bool
RTimer::isActive() const
{
  if(mHandle)
  {
    return xTimerIsTimerActive(mHandle);
  }
  else
  {
    return false;
  }
}

bool
RTimer::isSingleShot() const
{
  return mIsSingleShot;
}

void
RTimer::setInterval(int msec)
{
  mInterval = msec;
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
  return static_cast<int>(rShortenPtr(this));
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

  // NOTE: Set timer run as idle task by default, but we can't set interval to
  // zero, otherwise the created timer will return to NULL, so we give value 1 .
  mHandle = xTimerCreate(
    "",
    (mInterval <= 0) ? 1 : (mInterval / portTICK_PERIOD_MS),
    mIsSingleShot ? pdTRUE : pdFALSE,
    this,
    onTimeout
    );

  xTimerStart(mHandle, 0);
}

void
RTimer::stop()
{
  xTimerStop(mHandle, 0);
  mHandle = 0;
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
