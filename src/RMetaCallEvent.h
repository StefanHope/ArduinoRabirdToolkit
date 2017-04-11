#ifndef __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C
#define __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C

#include "REvent.h"
#include "RDelegate.h"

class RMetaCallEvent : public REvent
{
public:
  typedef typename Rt::Delegate<void ()>::BaseType Delegate;

  explicit
  RMetaCallEvent(const rcount &type, Delegate aDelegate);

  const Delegate &
  delegate();

private:
  Delegate mDelegate;
};

#endif // __INCLUDED_0D3B3BD21E8411E7AA6EA088B4D1658C
