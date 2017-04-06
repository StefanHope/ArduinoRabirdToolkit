#ifndef __INCLUDED_231AF942C35811E6AA6EA088B4D1658C
#define __INCLUDED_231AF942C35811E6AA6EA088B4D1658C

#include "RRealtimeTimer.h"

class RTimer : public RRealtimeTimer
{
public:
  RTimer();
  ~RTimer();

  bool
  event(REvent *e);

  template <class DelegateType>
  static void
  singleShot(int msec, const DelegateType &delegate);

  RSignal<void()> timeout;

  // Not allow override these functions ! End for RTimer!

private:
  bool
  _isRestartFromCallback();
  void
  _redirectEvents();
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
