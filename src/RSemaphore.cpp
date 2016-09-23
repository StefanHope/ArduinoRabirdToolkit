#include "RSemaphore.h"

RSemaphore::RSemaphore(int n)
  : mHandle(xSemaphoreCreateCounting(n, 0))
{
}

RSemaphore::~RSemaphore()
{
}

void
RSemaphore::acquire(int n)
{
  tryAcquire(n, portMAX_DELAY);
}

int
RSemaphore::available() const
{
}

void
RSemaphore::release(int n)
{
  for(auto i = 0; i < n; ++i)
  {
    xSemaphoreGive(mHandle);
  }
}

bool
RSemaphore::tryAcquire(int n)
{
  return tryAcquire(n, 0);
}

bool
RSemaphore::tryAcquire(int n, int timeout)
{
  auto ticks = timeout / portTICK_PERIOD_MS;

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
