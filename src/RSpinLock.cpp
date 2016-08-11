#include "RSpinLock.h"
#include <Arduino.h>

RSpinLock::RSpinLock()
{
  noInterrupts();
}

RSpinLock::~RSpinLock()
{
  interrupts();
}
