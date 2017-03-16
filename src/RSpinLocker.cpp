#include "RSpinLocker.h"
#include "RIsr.h"

RSpinLocker::RSpinLocker()
{
  if(_rIsrExecuting())
  {
    return;
  }

  vTaskSuspendAll();
}

RSpinLocker::~RSpinLocker()
{
  if(_rIsrExecuting())
  {
    return;
  }

  xTaskResumeAll();
}
