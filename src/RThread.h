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
  /**
   * This enum type indicates how the operating system should schedule newly
   * created threads.
   */
  enum Priority
  {
    /// scheduled only when no other threads are running.
    IdlePriority /* = tskIDLE_PRIORITY */,
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

private:
  RThread(TaskHandle_t handle);

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
  bool
  wait(unsigned long time=std::numeric_limits<unsigned long>::max());

  void
  quit();
  void
  start(Priority priority=NormalPriority);
  void
  terminate();
  REventLoop *
  eventLoop();
  static RThread *
  currentThread();
  static TaskHandle_t
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
  size_t       mStackSize;
  TaskHandle_t mHandle;
  bool         mIsOwnded;
  REventLoop * mEventLoop;

  friend RThreadPrivate;
  friend REventLoop;
  friend RCoreApplication;

  R_DISABLE_COPY(RThread)
};

#endif // __INCLUDED_458662EC691611E6AA6E0021CC66E280
