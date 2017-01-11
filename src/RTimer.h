#ifndef __INCLUDED_231AF942C35811E6AA6EA088B4D1658C
#define __INCLUDED_231AF942C35811E6AA6EA088B4D1658C

#include "RObject.h"
#include "RSignal.h"
#include "timers.h"

class RTimer : public RObject
{
public:
  RTimer();
  ~RTimer();

  int
  interval() const;
  bool
  isActive() const;
  bool
  isSingleShot() const;
  void
  setInterval(int msec);
  void
  setSingleShot(bool singleShot);
  int
  timerId() const;

  void
  start(int msec);
  void
  start();
  void
  stop();

  bool
  event(REvent *e);

  RSignal<void()> timeout;

private:
  static void
  onTimeout(TimerHandle_t handle);
  bool          mIsSingleShot;
  int           mInterval;
  TimerHandle_t mHandle;
};

#endif // __INCLUDED_231AF942C35811E6AA6EA088B4D1658C
