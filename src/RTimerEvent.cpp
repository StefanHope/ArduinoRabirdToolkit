#include "RTimerEvent.h"

RTimerEvent::RTimerEvent(rcount type, int timerId)
  : BaseType(type)
  , mTimerId(timerId)
{
}

RTimerEvent::~RTimerEvent()
{
}

int
RTimerEvent::timerId() const
{
  return mTimerId;
}
