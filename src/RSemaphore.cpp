#include "RSemaphore.h"

RSemaphore::RSemaphore(rcount n)
  : mHandle(xSemaphoreCreateCounting(n, 0))
{
}

RSemaphore::~RSemaphore()
{
}

void
RSemaphore::acquire(rcount n)
{
  R_WAIT_UNTIL(tryAcquire(n, portMAX_DELAY));
}

int
RSemaphore::available() const
{
}

void
RSemaphore::release(rcount n)
{
  for(auto i = 0; i < n; ++i)
  {
    xSemaphoreGive(mHandle);
  }
}

bool
RSemaphore::tryAcquire(rcount n)
{
  return tryAcquire(n, 0);
}

bool
RSemaphore::tryAcquire(rcount n, int ms)
{
  auto ticks = ms / portTICK_PERIOD_MS;

  for(auto i = 0; i < n; ++i)
  {
    // If failed we should release all acquired.
    if(pdFALSE == xSemaphoreTake(mHandle, ticks))
    {
      release(i + 1);

      return false;
    }
  }

  return true;
}
