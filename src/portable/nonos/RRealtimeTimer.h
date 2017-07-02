#ifndef __INCLUDED_D098FB305D5611E7AA6EA088B4D1658C
#define __INCLUDED_D098FB305D5611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RSignal.h"
#include "RAtomicInteger.h"
#include "RTimerQueue.h"
#include <list>

class RRealtimeTimer : public RObject
{
public:
  RRealtimeTimer();
  ~RRealtimeTimer();

  int32_t
  interval() const;
  bool
  isActive() const;
  bool
  isSingleShot() const;
  /**
   * @brief setInterval
   *
   * In 16bits tick mode, we only support 23bits msecs without size enlarge (
   * 8388608 ms at maximum, about 2.3 hours)
   *
   * @param msec
   * @ref configUSE_16_BIT_TICKS
   */
  void
  setInterval(int32_t msec);
  void
  setSingleShot(bool singleShot);
  int
  timerId() const;

  void
  start();
  void
  start(int32_t msec);
  void
  stop();

  virtual
  void
  run();

private:
  /**
   * @brief _isRestartFromCallback
   *
   * Determine if we should restart timer during timer callback (inside the
   * timer daemon thread!)
   * @return
   */
  virtual
  bool
  _isRestartFromCallback();
  virtual
  void
  _redirectEvents();

private:
  bool    mIsSingleShot;
  int32_t mInterval;

  /**
   * @brief mIt
   *
   * The iterator of the timer inside timer queue of event loop.
   * So that we could fast start / stop the specific timer.
   */
  RTimerQueue::iterator mIt;

  friend class RTimer;
  friend class REventLoop;
};

#endif // __INCLUDED_D098FB305D5611E7AA6EA088B4D1658C
