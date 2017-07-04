#include "RThread.h"
#include "REventLoop.h"
#include "RForwardList.h"
#include "RSpinLocker.h"
#include "RIsr.h"
#include "RMain.h"

struct EventLoopItem
{
  REventLoop *loop;

  RThread::Id threadId;
};

class RThreadPrivate
{
public:
  static void
  run(void *arg);
};

#ifdef R_OS_NONOS
static RThread::Id sNonOSThreadId =
  reinterpret_cast<RThread::Id>(&sNonOSThreadId);

#endif

static const rtime sTimeBlockMax = std::numeric_limits<rtime>::max() /
                                   1000;

#ifdef R_OS_FREERTOS
static const rtime sTickBlock     = sTimeBlockMax / portTICK_PERIOD_MS;  /**< ms value matched ticks */
static const rtime sTickBlockToMS = sTickBlock * portTICK_PERIOD_MS;  /**< ms value */
static const rtime sTickBlockToUS = sTickBlockToMS * 1000;  /**< us value */

#endif // #ifdef R_OS_FREERTOS

// FIXME: Thread list not guarded by mutex now !
static RForwardList<RThread *>     sThreads;
static RForwardList<EventLoopItem> sEventLoops;
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

#ifdef R_OS_FREERTOS
  // We must delete self when want to exit a task.
  // Reference to "Implementing a Task" section of FreeRTOS.
  vTaskDelete(NULL);
#endif // #ifdef R_OS_FREERTOS
}

RThread::RThread(RThread::Id handle)
// So that RObject won't create another RThread lead infinite looping
  : RObject(this)
#ifdef R_OS_FREERTOS
  , mStackSize(configMINIMAL_STACK_SIZE * sizeof(word))
#else
  , mStackSize(85 * sizeof(word))
#endif
  , mHandle(handle)
  , mIsOwnded(false)
  , mEventLoop(NULL)
{
  // Find matched event loop for specific task.
  for(auto it = sThreads.begin(); it != sThreads.end(); ++it)
  {
    if(handle == (*it)->mHandle)
    {
      mEventLoop = (*it)->eventLoop();
      break;
    }
  }

  // FIXME: New event loop will generated for task 0 and without free!
  if(NULL == mEventLoop)
  {
    R_MAKE_SPINLOCKER();
    sThreads.pushFront(this);
  }
}

RThread::RThread()
  : RObject(this)
#ifdef R_OS_FREERTOS
  , mStackSize(configMINIMAL_STACK_SIZE * sizeof(word))
#else
  , mStackSize(85 * sizeof(word))
#endif
  , mHandle(NULL)
  , mIsOwnded(false)
  , mEventLoop(NULL)
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
  eventLoop()->exit(returnCode);
}

bool
RThread::isFinished() const
{
  if(!mHandle)
  {
    return true;
  }

#if defined(R_OS_FREERTOS)
  return (eDeleted == eTaskGetState(mHandle));
#else // #if defined(R_OS_FREERTOS)
  // FIXME: Not implemented
  return false;
#endif // #if defined(R_OS_FREERTOS)
}

bool
RThread::isRunning() const
{
  if(!mHandle)
  {
    return false;
  }

#if defined(R_OS_FREERTOS)
  return (eDeleted != eTaskGetState(mHandle));
#else // #if defined(R_OS_FREERTOS)
  // FIXME: Not implemented
  return true;
#endif // #if defined(R_OS_FREERTOS)
}

RThread::Priority
RThread::priority() const
{
  if(!mHandle)
  {
    return IdlePriority;
  }

#if defined(R_OS_FREERTOS)
  return static_cast<RThread::Priority>(uxTaskPriorityGet(mHandle));
#else // #if defined(R_OS_FREERTOS)
  // FIXME: Not implemented
  return NormalPriority;
#endif // #if defined(R_OS_FREERTOS)
}

void
RThread::setPriority(RThread::Priority priority)
{
  if(!mHandle)
  {
    return;
  }

#if defined(R_OS_FREERTOS)
  vTaskPrioritySet(mHandle, static_cast<UBaseType_t>(priority));
#else // #if defined(R_OS_FREERTOS)
  // FIXME: Not implemented
#endif // #if defined(R_OS_FREERTOS)
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

RThread::Id
RThread::id() const
{
  return mHandle;
}

bool
RThread::wait(unsigned long time)
{
  /// FIXME: Ugly way to wait for thread finished.

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

    /* Block for 100ms each time */
    msleep(100);
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
  RThread::Id handle = NULL;

  if(isRunning())
  {
    return;
  }

  terminate();

#ifdef R_OS_FREERTOS

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

#else // #ifdef R_OS_FREERTOS
  mIsOwnded = false;
  mHandle   = sNonOSThreadId;

#endif // #ifdef R_OS_FREERTOS
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

      { // Remove event loop from event loop list
        auto prevIt = sEventLoops.beforeBegin();
        auto it     = sEventLoops.begin();

        for(; it != sEventLoops.end(); ++it)
        {
          if(mHandle == it->threadId)
          {
            sEventLoops.eraseAfter(prevIt);
            break;
          }

          prevIt = it;
        }
      }

      delete mEventLoop;
      mEventLoop = NULL;

#ifdef R_OS_FREERTOS
      vTaskDelete(mHandle);
#endif // #ifdef R_OS_FREERTOS
    }

    terminated.emit();
  }

  mHandle = NULL;
}

REventLoop *
RThread::eventLoop()
{
  if(NULL == mHandle)
  {
    return NULL;
  }

  if(NULL == mEventLoop)
  {
    R_MAKE_SPINLOCKER();

    if(mEventLoop) // Avoid previous check passed at the same time.
    {
      return mEventLoop;
    }

    { // Find if there already matched event loop .
      for(auto it = sEventLoops.begin(); it != sEventLoops.end(); ++it)
      {
        if(mHandle == it->threadId)
        {
          mEventLoop = it->loop;
          break;
        }
      }
    }

    if(NULL == mEventLoop)
    {
      mEventLoop = new REventLoop();
      mEventLoop->moveToThread(const_cast<RThread *>(this));

      EventLoopItem item;

      item.loop     = mEventLoop;
      item.threadId = mHandle;
      sEventLoops.pushFront(item);
    }
  }

  return mEventLoop;
}

RThread *
RThread::currentThread()
{
  RThread::Id handle = currentThreadId();

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

RThread::Id
RThread::currentThreadId()
{
#ifdef R_OS_FREERTOS
  return xTaskGetCurrentTaskHandle();
#else // #ifdef R_OS_FREERTOS
  return sNonOSThreadId;
#endif // #ifdef R_OS_FREERTOS
}

void
RThread::yieldCurrentThread()
{
#ifdef R_OS_FREERTOS

  if(_rIsrExecuting())
  {
    return;
  }

  taskYIELD();
#endif // #ifdef R_OS_FREERTOS
}

int
RThread::exec()
{
  return eventLoop()->exec();
}

void
RThread::run()
{
  exec();
}

void
RThread::msleep(rtime msecs)
{
  // I don't know why, but we can't use vTaskDelay() inside the idle task !
  // Otherwise the program crash!
#ifdef R_OS_FREERTOS

  if(currentThreadId() && (currentThreadId() != rGetMainThread()->id()))
  {
    while(msecs > 0)
    {
      if(msecs < sTickBlockToMS)
      {
        // Convert to ticks
        vTaskDelay(msecs / portTICK_PERIOD_MS);
        break;
      }

      vTaskDelay(sTickBlock);
      msecs -= sTickBlockToMS;
    }
  }
  else
#endif // #ifdef R_OS_FREERTOS
  {
    // Simple delay
    delay(msecs);
  }
}

void
RThread::sleep(rtime secs)
{
  /**< Time block to milliseconds */
  static const rtime sTimeBlockToMS = sTimeBlockMax * 1000;

  while(secs > 0)
  {
    if(secs < sTimeBlockMax)
    {
      msleep(secs * 1000);
      break;
    }

    msleep(sTimeBlockToMS);

    secs -= sTimeBlockMax;
  }
}

void
RThread::usleep(rtime usecs)
{
#ifdef R_OS_FREERTOS

  // I don't know why, but we can't use vTaskDelay() inside the idle task !
  // Otherwise the program crash!
  if(currentThreadId() && (currentThreadId() != rGetMainThread()->id()))
  {
    while(usecs > 0)
    {
      if(usecs < sTickBlockToUS)
      {
        // Convert to ticks
        vTaskDelay(usecs / (1000 * portTICK_PERIOD_MS));
        break;
      }

      vTaskDelay(sTickBlock);
      usecs -= sTickBlockToUS;
    }
  }
  else
#endif // #ifdef R_OS_FREERTOS
  {
    delayMicroseconds(usecs);
  }
}
