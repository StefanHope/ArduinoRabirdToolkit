#include "RSpinLock.h"
#include <Arduino.h>

RSpinLock::RSpinLock()
{
  mOldRegisters = SREG;
  noInterrupts();
}

RSpinLock::~RSpinLock()
{
  SREG = mOldRegisters;
}
