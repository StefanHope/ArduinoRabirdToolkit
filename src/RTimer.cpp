#include "RTimer.h"
#include "RTimerEvent.h"
#include "RCoreApplication.h"
#include "RScopedPointer.h"
#include "RIsr.h"
#include "RThread.h"

RTimer::RTimer()
{
}

RTimer::~RTimer()
{
}

bool
RTimer::event(REvent *e)
{
  if(e->type() == RTimerEvent::sType)
  {
    // FIXME: Here may be generate a potential crash
    auto timerEvent = static_cast<RTimerEvent *>(e);

    timeout.emit();

    if(!isSingleShot())
    {
      start(); // Restart timer for next round
    }

    timerEvent->accept();
    return true;
  }

  return RRealtimeTimer::event(e);
}

bool
RTimer::_isRestartFromCallback()
{
  return false;
}

void
RTimer::run()
{
  // NOTE: Event will be deleted in REventLoop after they handled that event.
  RCoreApplication::postEvent(this, rMakeEvent<RTimerEvent>(timerId()));
}
