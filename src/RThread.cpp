#include "RThread.h"
#include "REventLoop.h"
#include "RForwardList.h"
#include "RSpinLocker.h"

class RThreadPrivate
{
public:
  static void
  run(void *arg);
};

// FIXME: Thread list not guarded by mutex now !
static RForwardList<RThread *> sThreads;
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

  // We must delete self when wan't to exit a task.
  // Reference to "Implementing a Task" section of FreeRTOS.
  vTaskDelete(NULL);
}

RThread::RThread(TaskHandle_t handle)
// So that RObject won't create another RThread lead infinite looping
  : RObject(this)
  , mStackSize(128)
  , mHandle(handle)
  , mIsOwnded(false)
{
}

RThread::RThread()
  : RObject(this)
  , mStackSize(128)
  , mHandle(NULL)
  , mIsOwnded(false)
{
  R_MAKE_SPINLOCKER();
  sThreads.pushFront(this);
}

RThread::~RThread()
{
  terminate();

  R_MAKE_SPINLOCKER();

  // Clear this thread pointer in thread list
  sThreads.remove(this);
}

void
RThread::exit(int returnCode)
{
  REventLoop::instance(this)->exit(returnCode);
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

size_t
RThread::stackSize() const
{
  return mStackSize;
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

  if(InheritPriority == priority)
  {
    priority =
      static_cast<RThread::Priority>(uxTaskPriorityGet(currentThreadId()));
  }

  auto ret = xTaskCreate(
    RThreadPrivate::run,  /* Function that implements the task. */
    "",                /* Text name for the task. */
    (stackSize() + 1) / sizeof(uint16_t), /* Stack size in words, not bytes. */
    static_cast<void *>(this),      /* Parameter passed into the task. */
    priority,  /* Priority at which the task is created. */
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
    // Ensure no tasks and interrupts will be trigger during thread event loop
    // destruction.
    {
      R_MAKE_SPINLOCKER();
      REventLoop::_destroy(this);
      vTaskDelete(mHandle);
    }

    terminated.emit();
  }

  mHandle = NULL;
}

RThread *
RThread::currentThread()
{
  TaskHandle_t handle = currentThreadId();

  for(auto it = sThreads.begin(); it != sThreads.end(); ++it)
  {
    if(handle == (*it)->mHandle)
    {
      return *it;
    }
  }

  // FIXME: Here generated an orphan RThread object!
  return new RThread(handle);
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

int
RThread::exec()
{
  REventLoop *loop = REventLoop::instance(this);

  return loop->exec();
}

void
RThread::run()
{
  exec();
}

void
RThread::msleep(unsigned long msecs)
{
  unsigned long blockMS = std::numeric_limits<unsigned long>::max() / 1000;
  unsigned long blockUS = blockMS * 1000;

  while(msecs > 0)
  {
    if(msecs < blockMS)
    {
      blockMS = msecs;
      blockUS = blockMS * 1000;
    }

    usleep(blockUS);

    msecs -= blockMS;
  }
}

void
RThread::sleep(unsigned long secs)
{
  unsigned long blockS  = std::numeric_limits<unsigned long>::max() / 1000;
  unsigned long blockMS = blockS * 1000;

  while(secs > 0)
  {
    if(secs < blockMS)
    {
      blockS  = secs;
      blockMS = blockS * 1000;
    }

    msleep(blockMS);

    secs -= blockS;
  }
}

void
RThread::usleep(unsigned long usecs)
{
  unsigned long ticks = usecs / (1000 * portTICK_PERIOD_MS);

  auto maxTicks = static_cast<decltype(usecs)>(portMAX_DELAY);

  if(ticks <= 0)
  {
    ticks = 1;
    usecs = portTICK_PERIOD_MS * 1000;
  }

  if(currentThreadId())
  {
    while(ticks > 0)
    {
      if(ticks < maxTicks)
      {
        maxTicks = ticks;
      }

      vTaskDelay(maxTicks);
      ticks -= maxTicks;
    }
  }
  else
  {
    delayMicroseconds(usecs);
  }
}
