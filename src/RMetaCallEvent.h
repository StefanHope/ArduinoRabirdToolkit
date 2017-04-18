#ifndef __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C
#define __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C

#include "REvent.h"
#include "RSlot.h"

class RMetaCallEvent : public REvent
{
public:
  typedef typename Rt::Slot<void ()>::BaseType Slot;

  explicit
  RMetaCallEvent(const rcount &type, Slot slot);

  const Slot &
  slot();

private:
  Slot mSlot;
};

#endif // __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C
