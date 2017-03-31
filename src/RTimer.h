#ifndef __INCLUDED_231AF942C35811E6AA6EA088B4D1658C
#define __INCLUDED_231AF942C35811E6AA6EA088B4D1658C

#include "RObject.h"
#include "RSignal.h"
#include "timers.h"
#include "RAtomicInteger.h"

class RTimer : public RObject
{
public:
  RTimer();
  ~RTimer();

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

  bool
  event(REvent *e);

  template <class DelegateType>
  static void
  singleShot(int msec, const DelegateType &delegate);

  RSignal<void()> timeout;

private:
  static void
  onTimeout(TimerHandle_t handle);
  TimerHandle_t mHandle;

  class
  {
public:
    bool    mIsSingleShot : 1;
    uint8_t mExtended     : 7;
  };

#if (configUSE_16_BIT_TICKS == 1)
  RAtomicInteger<uint8_t> mExtendedCounter;

#endif
};

template <class DelegateType>
void
RTimer::singleShot(int msec, const DelegateType &delegate)
{
  auto timer = new RTimer();
  timer->timeout.connect(delegate);
  timer->timeout.connect(timer, &RTimer::deleteLater);
  timer->setSingleShot(true);
  timer->setInterval(msec);
  timer->start();
}

#endif // __INCLUDED_231AF942C35811E6AA6EA088B4D1658C
