#include "RSpinLocker.h"
#include <Arduino.h>

RSpinLocker::RSpinLocker()
{
  mOldRegisters = SREG;
  noInterrupts();
}

RSpinLocker::~RSpinLocker()
{
  SREG = mOldRegisters;
}
