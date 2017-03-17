#include "RIsr.h"
#include "RSpinLocker.h"

#define _R_IMPLEMENT_ISR(number) _R_IMPLEMENT_ISR1(number)
#define _R_IMPLEMENT_ISR1(number) \
  void __rIsr##number() \
  { \
    noInterrupts(); \
    sIsrExecuting = true; \
    sContexts[number].triggered.emit(); \
    interrupts(); \
    sIsrExecuting = false; \
  }

static volatile int8_t sIsrExecuting = false;
static int8_t          sIndex        = -1;
static RIsrContext *   sContexts     = NULL;

_R_IMPLEMENT_ISR(0)
_R_IMPLEMENT_ISR(1)
_R_IMPLEMENT_ISR(2)
_R_IMPLEMENT_ISR(3)
_R_IMPLEMENT_ISR(4)
_R_IMPLEMENT_ISR(5)
_R_IMPLEMENT_ISR(6)
_R_IMPLEMENT_ISR(7)

void
_rIsrInitialize()
{
  R_MAKE_SPINLOCKER();

  sContexts        = new RIsrContext[_R_MAX_ISRS];
  sContexts[0].isr = &__rIsr0;
  sContexts[1].isr = &__rIsr1;
  sContexts[2].isr = &__rIsr2;
  sContexts[3].isr = &__rIsr3;
  sContexts[4].isr = &__rIsr4;
  sContexts[5].isr = &__rIsr5;
  sContexts[6].isr = &__rIsr6;
  sContexts[7].isr = &__rIsr7;
}

void
_rIsrFinalize()
{
  R_MAKE_SPINLOCKER();

  if(sContexts)
  {
    delete[] sContexts;
  }
}

RIsrContext *
_rIsrAllocate()
{
  R_MAKE_SPINLOCKER();

  if(NULL == sContexts)
  {
    _rIsrInitialize();
  }

  if((sIndex + 1) >= _R_MAX_ISRS)
  {
    return NULL;
  }

  return &sContexts[sIndex++];
}

bool
_rIsrExecuting()
{
  return sIsrExecuting;
}
