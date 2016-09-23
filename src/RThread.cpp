#include "RThread.h"

class RThreadPrivate
{
public:
  static void
  run(void *arg);
};

void
RThreadPrivate::run(void *arg)
{
  RThread *thread = static_cast<RThread *>(arg);

  if(thread)
  {
    thread->started.emit();
    thread->run();
    thread->finished.emit();
  }
}

RThread::RThread(TaskHandle_t handle) : RThread()
{
  mHandle = handle;
}

RThread::RThread()
  : mStackSize(128)
  , mHandle(NULL)
  , mIsOwnded(false)
{
}

RThread::~RThread()
{
  terminate();
}

void
RThread::exit(int returnCode)
{
  // FIXME: We should post a message to this thread's queue just tell the thread
  // with specific exit code. Now just simple terminate() this thread (very
  // dangerous)
  terminate();
}

bool
RThread::isFinished() const
{
  if(!mHandle)
  {
    return true;
  }

  return (eDeleted == eTaskGetState(mHandle));
}

bool
RThread::isRunning() const
{
  if(!mHandle)
  {
    return false;
  }

  return (eDeleted != eTaskGetState(mHandle));
}

RThread::Priority
RThread::priority() const
{
  if(!mHandle)
  {
    return IdlePriority;
  }

  return static_cast<RThread::Priority>(uxTaskPriorityGet(mHandle));
}

void
RThread::setPriority(RThread::Priority priority)
{
  if(!mHandle)
  {
    return;
  }

  vTaskPrioritySet(mHandle, static_cast<UBaseType_t>(priority));
}

void
RThread::setStackSize(size_t stackSize)
{
  mStackSize = stackSize;
}

bool
RThread::wait(unsigned long time)
{
  /// FIXME: Ugly way to wait for thread finished.

  /* Block for 100ms each time */
  const TickType_t ticksPerBlock = 100 / portTICK_PERIOD_MS;

  if(currentThreadId() == mHandle)
  {
    // You can't wait yourself in the samethread!
    return false;
  }

  while(true)
  {
    if(isFinished())
    {
      return true;
    }

    if(time < std::numeric_limits<unsigned long>::max())
    {
      if(time <= 100)
      {
        // Timeout!
        return false;
      }
      else
      {
        time -= 100;
      }
    }

    vTaskDelay(ticksPerBlock);
  }
}

void
RThread::quit()
{
  this->exit(0);
}

void
RThread::start(RThread::Priority priority)
{
  /* Create the task, storing the handle. */
  TaskHandle_t handle = NULL;

  if(isRunning())
  {
    return;
  }

  terminate();

  UBaseType_t targetPriority = IdlePriority;

  if(InheritPriority == priority)
  {
    targetPriority = uxTaskPriorityGet(currentThreadId());
  }

  auto ret = xTaskCreate(
    RThreadPrivate::run,  /* Function that implements the task. */
    "",                /* Text name for the task. */
    (stackSize() + 1) % sizeof(uint16_t), /* Stack size in words, not bytes. */
    static_cast<void *>(this),      /* Parameter passed into the task. */
    targetPriority,  /* Priority at which the task is created. */
    &handle);   /* Used to pass out the created task's handle. */

  if(ret == pdPASS)
  {
    mIsOwnded = true;
    mHandle   = handle;
  }
}

void
RThread::terminate()
{
  if(mIsOwnded && mHandle)
  {
    vTaskDelete(mHandle);
    terminated.emit();
  }

  mHandle = NULL;
}

TaskHandle_t
RThread::currentThreadId()
{
  return xTaskGetCurrentTaskHandle();
}

void
RThread::yieldCurrentThread()
{
  taskYIELD();
}

void
RThread::run()
{
  // TODO: We sould run event loop here!
}

void
RThread::msleep(unsigned long msecs)
{
  unsigned long blockTime = std::numeric_limits<unsigned long>::max() / 1000;

  while(msecs > 0)
  {
    if(msecs <= std::numeric_limits<unsigned long>::max())
    {
      usleep(msecs);
      return;
    }

    usleep(std::numeric_limits<unsigned long>::max());
    msecs -= blockTime;
  }
}

void
RThread::sleep(unsigned long secs)
{
  unsigned long blockTime = std::numeric_limits<unsigned long>::max() /
                            1000000l;

  while(secs > 0)
  {
    if(secs <= std::numeric_limits<unsigned long>::max())
    {
      usleep(secs);
      return;
    }

    usleep(std::numeric_limits<unsigned long>::max());
    secs -= blockTime;
  }
}

void
RThread::usleep(unsigned long usecs)
{
  unsigned long ticks = usecs / (1000 * portTICK_PERIOD_MS);

  while(ticks > 0)
  {
    if(ticks <= static_cast<decltype(usecs)>(portMAX_DELAY))
    {
      vTaskDelay(static_cast<decltype(portMAX_DELAY)>(ticks));
      return;
    }

    vTaskDelay(portMAX_DELAY);
    ticks -= static_cast<decltype(usecs)>(portMAX_DELAY);
  }
}
