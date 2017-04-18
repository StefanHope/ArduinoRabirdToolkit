#include "RSlot.h"

Rt::Slot<void()>
rMakeSlot(void (*func)())
{
  return Rt::Slot<void()>(func);
}
