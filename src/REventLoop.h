#ifndef __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C
#define __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C

#include "RObject.h"
#include "REvent.h"
#include <list>

class RCoreApplication;
class REventLoop : public RObject
{
private:
  struct EventData
  {
    RObject *receiver;
    REvent * event;

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

protected:
  void
  postEvent(RObject *receiver, REvent *event);

  void
  clear();

  bool
  hasPendingEvents();

private:
  // FIXME: Events are not be protected by mutex, they will be crashed during
  // access.
  std::list<EventData> mEvents;
  int  mReturnCode;
  bool mIsInterrupt;

  friend RThread;
  friend RCoreApplication;
};

#endif // __INCLUDED_2CAAC4E6954111E6AA6EA088B4D1658C
