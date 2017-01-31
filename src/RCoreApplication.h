#ifndef __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C
#define __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C

#include "RObject.h"
#include "RScopedPointer.h"

class REvent;
class REventLoop;
class RNullStream;
class RCoreApplication : public RObject
{
public:
  RCoreApplication();
  ~RCoreApplication();

  /**
   * Return a stream can output any data to it but without do any real write
   * behavior.
   *
   * @brief nullStream
   * @return
   */
  RNullStream *
  nullStream();
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
  RScopedPointer<RNullStream> mNullStream;
};

#define rCoreApp (RCoreApplication::instance())

#endif // __INCLUDED_9B933A8E8FBD11E6AA6EA088B4D1658C
