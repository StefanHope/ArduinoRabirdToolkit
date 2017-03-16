#ifndef __INCLUDED_D5F5D7DA09F311E7AA6EA088B4D1658C
#define __INCLUDED_D5F5D7DA09F311E7AA6EA088B4D1658C

#include "RSignal.h"

#define _R_MAX_ISRS 8

#define _R_DECLARE_ISR(number)  _R_DECLARE_ISR1(number)
#define _R_DECLARE_ISR1(number) extern void __rIsr##number();

struct RIsrContext
{
  void (*isr)();

  RSignal<void()> triggered;
};

_R_DECLARE_ISR(0)
_R_DECLARE_ISR(1)
_R_DECLARE_ISR(2)
_R_DECLARE_ISR(3)
_R_DECLARE_ISR(4)
_R_DECLARE_ISR(5)
_R_DECLARE_ISR(6)
_R_DECLARE_ISR(7)

void
_rIsrInitialize();

void
_rIsrFinalize();

RIsrContext *
_rIsrAllocate();

template <class ... ParamTypes>
void
_rIsrAttach(void *isrId, int8_t mode, ParamTypes ... params)
{
  R_MAKE_SPINLOCKER();
  auto context = _rIsrAllocate();

  context->triggered.connect(params ...);
  attachInterrupt(isrId, context->isr, mode);
}

#endif // __INCLUDED_D5F5D7DA09F311E7AA6EA088B4D1658C
