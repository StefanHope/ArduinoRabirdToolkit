#ifndef __INCLUDED_458662EC691611E6AA6E0021CC66E280
#define __INCLUDED_458662EC691611E6AA6E0021CC66E280

#include "RObject.h"
#include "RSignal.h"
#include <limits>

class REventLoop;
class RThreadPrivate;
class RCoreApplication;
class RThread : public RObject
{
public:
#ifdef R_OS_FREERTOS
  typedef TaskHandle_t Id;

#else
  struct IdContext
  {
    int value;
  };

  typedef struct IdContext *Id;

#endif // #ifdef R_OS_FREERTOS

  /**
   * This enum type indicates how the operating system should schedule newly
   * created threads.
   */
#if defined(R_OS_FREERTOS)
  enum Priority
  {
    /// scheduled only when no other threads are running.
    IdlePriority = 0 /* = tskIDLE_PRIORITY */,
    /// scheduled less often than LowPriority.
    LowestPriority = configMAX_PRIORITIES / 7,
    /// scheduled less often than NormalPriority.
    LowPriority = configMAX_PRIORITIES / 4,
    /// the default priority of the operating system.
    NormalPriority = configMAX_PRIORITIES / 2,
    /// scheduled more often than NormalPriority.
    HighPriority = NormalPriority + LowestPriority,
    /// scheduled more often than HighPriority.
    HighestPriority = NormalPriority + LowPriority,
    /// scheduled as often as possible.
    TimeCriticalPriority = configMAX_PRIORITIES - 1,
    /// use the same priority as the creating thread. This is the default.
    InheritPriority,
  };

#else // #if defined(R_OS_FREERTOS)
  enum Priority
  {
    /// scheduled only when no other threads are running.
    IdlePriority = 0 /* = tskIDLE_PRIORITY */,
    /// scheduled less often than LowPriority.
    LowestPriority,
    /// scheduled less often than NormalPriority.
    LowPriority,
    /// the default priority of the operating system.
    NormalPriority,
    /// scheduled more often than NormalPriority.
    HighPriority,
    /// scheduled more often than HighPriority.
    HighestPriority,
    /// scheduled as often as possible.
    TimeCriticalPriority,
    /// use the same priority as the creating thread. This is the default.
    InheritPriority,
  };

#endif // #if defined(R_OS_FREERTOS)

private:
  RThread(RThread::Id handle);

public:
  RThread();

  virtual
  ~RThread();

  /**
   * Tells the thread's event loop to exit with a return code.
   *
   * @brief exit
   * @param returnCode
   * @note Not implemented
   */
  void
  exit(int returnCode=0);
  bool
  isFinished() const;
  bool
  isRunning() const;
  Priority
  priority() const;
  void
  setPriority(Priority priority);
  void
  setStackSize(size_t stackSize);
  size_t
  stackSize() const;
  Id
  id() const;
  bool
  wait(unsigned long time=std::numeric_limits<unsigned long>::max());

  void
  quit();
  void
  start(Priority priority=InheritPriority);
  void
  terminate();
  REventLoop *
  eventLoop();
  static RThread *
  currentThread();
  static RThread::Id
  currentThreadId();
  static void
  yieldCurrentThread();
  static void
  msleep(rtime msecs);
  static void
  sleep(rtime secs);
  static void
  usleep(rtime usecs);

  RSignal<void()> started;
  RSignal<void()> finished;
  RSignal<void()> terminated;

protected:
  int
  exec();
  virtual void
  run();

private:
  size_t mStackSize;

  RThread::Id mHandle;
  bool        mIsOwnded;
  REventLoop *mEventLoop;

  friend RThreadPrivate;
  friend REventLoop;
  friend RCoreApplication;

  R_DISABLE_COPY(RThread)
};

#endif // __INCLUDED_458662EC691611E6AA6E0021CC66E280
