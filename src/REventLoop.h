#ifndef __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C
#define __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C

#include "RObject.h"
#include "REvent.h"
#include "RSignal.h"
#include "RTimerQueue.h"
#include <list>

class RAbstractCoRoutine;
class RCoreApplication;
class RCoRoutine;
class RRealtimeTimer;
class REventLoop : public RObject
{
private:
  struct EventData
  {
    RObject *receiver;
    REvent * event;

    EventData()

      : receiver(NULL), event(NULL)
    {
    }

    EventData(RObject *inReceiver, REvent *inEvent)

      : receiver(inReceiver), event(inEvent)
    {
    }
  };

protected:
  REventLoop();

public:
  ~REventLoop();

  int
  exec();

  void
  exit(int returnCode=0);

  void
  quit();

  bool
  processEvents();

  void
  _attachCR(RCoRoutine *cr);

  void
  _detachCR(RCoRoutine *cr);

  RSignal<void()> idle;

  void
  postEvent(RObject *receiver, REvent *event);

protected:
  void
  clear();

  bool
  hasPendingEvents();

private:
  void
  execTimerQueue();

#if defined(R_OS_NONOS)
  void
  startTimer(RRealtimeTimer *timer);
  void
  stopTimer(RRealtimeTimer *timer);

  RTimerQueue mTimerQueue;

#endif // #if defined(R_OS_NONOS)

  // FIXME: Events are not be protected by mutex, they will be crashed during
  // access.
  std::list<EventData>    mEvents;
  std::list<RCoRoutine *> mCoRoutines;
  std::list<RObject *>    mDeferredObjects;
  int  mReturnCode;
  bool mIsInterrupt;

  friend RThread;
  friend RRealtimeTimer;
  friend RCoreApplication;
};

#endif // __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C
