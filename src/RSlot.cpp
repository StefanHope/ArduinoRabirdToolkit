#include "RSlot.h"

namespace Rt
{

Slot<void()>
MakeSlot(void (*func)())
{
  return Slot<void()>(func);
}
}
