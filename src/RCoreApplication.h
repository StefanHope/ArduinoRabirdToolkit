#ifndef __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C
#define __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C

#include "RObject.h"

class REvent;
class REventLoop;
class RCoreApplication : public RObject
{
public:
  RCoreApplication();
  ~RCoreApplication();

  static
  RCoreApplication *
  instance();
  static int
  exec();
  static void
  processEvents();
  static void
  postEvent(RObject *receiver, REvent *event);

private:
  REventLoop *mEventLoop;
};

#define rCoreApp (RCoreApplication::instance())

#endif // __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C
