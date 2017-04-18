#include "RMetaCallEvent.h"

RMetaCallEvent::RMetaCallEvent(const rcount &type, Slot slot)
  : REvent(type), mSlot(slot)
{
}

const RMetaCallEvent::Slot &
RMetaCallEvent::slot()
{
  return mSlot;
}
