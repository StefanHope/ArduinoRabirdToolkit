#include "RMain.h"
#include "RTypes.h"
#include "RThread.h"

class RMainThread : public RThread
{
public:
  void
  run();
};

void
RMainThread::run()
{
  static char  programName[] = "";
  static char *argv[]        = {programName, };

  rMain(1, argv);
}

void
setup()
{
  RMainThread *thread = new RMainThread();

  thread->setStackSize(256 + 128);
  thread->start();
}

void
loop()
{
  // Do nothing, we must not do anything inside loop(), it's necessary runtime
  // component for FreeRTOS. If you do complicate jobs, delay inside and take a
  // long time, it will lead some weird situation or lead program crash!
}
