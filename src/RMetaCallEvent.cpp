#include "RMetaCallEvent.h"

RMetaCallEvent::RMetaCallEvent(const rcount &type, Delegate aDelegate)
  : REvent(type), mDelegate(aDelegate)
{
}

const RMetaCallEvent::Delegate &
RMetaCallEvent::delegate()
{
  return mDelegate;
}
