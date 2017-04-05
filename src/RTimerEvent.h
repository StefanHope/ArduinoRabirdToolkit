#ifndef __INCLUDED_FE929E72C35C11E6AA6EA088B4D1658C
#define __INCLUDED_FE929E72C35C11E6AA6EA088B4D1658C

#include "REvent.h"

class RTimerEvent : public TypeEnumeratedEvent<REvent::Timer>
{
private:
  typedef RegisteredEventType BaseType;

public:
  RTimerEvent(rcount type, int timerId);
  ~RTimerEvent();

  int
  timerId() const;

private:
  const int mTimerId;
};

#endif // __INCLUDED_FE929E72C35C11E6AA6EA088B4D1658C
