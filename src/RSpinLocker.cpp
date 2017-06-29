#include "RSpinLocker.h"
#include "RIsr.h"

RSpinLocker::RSpinLocker()
{
#ifdef R_OS_FREERTOS

  if(_rIsrExecuting())
  {
    return;
  }

  vTaskSuspendAll();
#endif // #ifdef R_OS_FREERTOS
}

RSpinLocker::~RSpinLocker()
{
#ifdef R_OS_FREERTOS

  if(_rIsrExecuting())
  {
    return;
  }

  xTaskResumeAll();
#endif // #ifdef R_OS_FREERTOS
}
