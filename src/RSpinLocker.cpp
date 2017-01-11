#include "RSpinLocker.h"
#include <Arduino.h>

RSpinLocker::RSpinLocker()
{
  vTaskSuspendAll();
}

RSpinLocker::~RSpinLocker()
{
  xTaskResumeAll();
}
