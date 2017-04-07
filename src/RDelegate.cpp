#include "RDelegate.h"

namespace Rt
{

Delegate<void()>
MakeDelegate(void (*func)())
{
  return Delegate<void()>(func);
}
}
