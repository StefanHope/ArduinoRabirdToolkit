#include "RTimerEvent.h"

RTimerEvent::RTimerEvent(int timerId) : mTimerId(timerId)
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
