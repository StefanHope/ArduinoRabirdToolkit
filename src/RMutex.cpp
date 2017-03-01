#include "RMutex.h"

RMutex::RMutex(RMutex::RecursionMode mode)
  : mMode(mode), mHandle(NULL)
{
  if(NonRecursive == mode)
  {
    mHandle = xSemaphoreCreateMutex();
  }
  else
  {
    mHandle = xSemaphoreCreateRecursiveMutex();
  }
}

RMutex::~RMutex()
{
  if(mHandle)
  {
    vSemaphoreDelete(mHandle);
    mHandle = NULL;
  }
}

void
RMutex::lock()
{
  // INCLUDE_vTaskSuspend should specific to 1 for infinite loop !
  if(NonRecursive == mMode)
  {
    R_WAIT_UNTIL(xSemaphoreTake(mHandle, portMAX_DELAY));
  }
  else
  {
    R_WAIT_UNTIL(xSemaphoreTakeRecursive(mHandle, portMAX_DELAY));
  }
}

bool
RMutex::tryLock()
{
  return tryLock(0);
}

bool
RMutex::tryLock(int timeout)
{
  BaseType_t ret = pdFALSE;

  timeout = timeout / portTICK_PERIOD_MS;

  if(NonRecursive == mMode)
  {
    ret = xSemaphoreTake(mHandle, timeout);
  }
  else
  {
    ret = xSemaphoreTakeRecursive(mHandle, timeout);
  }

  return pdTRUE == ret;
}

void
RMutex::unlock()
{
  if(NonRecursive == mMode)
  {
    R_WAIT_UNTIL(xSemaphoreGive(mHandle));
  }
  else
  {
    R_WAIT_UNTIL(xSemaphoreGiveRecursive(mHandle));
  }
}
