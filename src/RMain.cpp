#include "RMain.h"
#include "RTypes.h"
#include "RThread.h"
#include "REventLoop.h"
#include "RCoreApplication.h"
#include "RSpinLocker.h"

static volatile RThread *sMainThread = NULL;
RThread *
rGetMainThread()
{
  return (RThread *)sMainThread;
}

void
setup()
{
}

void
loop()
{
  // Do nothing, we must not do time consuming inside loop(), it's necessary
  // runtime component for FreeRTOS. If you do complicate jobs, delay inside
  // and take a long time, it will lead some weird situation or lead program
  // crash!

  if(NULL == sMainThread)
  {
    const rfchar *programName = F("");
    rfchar *      argv[]      = {const_cast<rfchar *>(programName), };

    // FIXME: Idle thread only get working when other thread suspended (
    // vTaskDelay() or vTaskSuspend())

    // Fixed idle thread won't get any notice even yield from other thread
    vTaskPrioritySet(RThread::currentThreadId(), RThread::NormalPriority);

    sMainThread = RThread::currentThread();

    rMain(1, argv);
  }

  if(rCoreApp)
  {
    rCoreApp->processEvents();
  }
}

void
rPostEvent(RObject *receiver, REvent *event)
{
  R_MAKE_SPINLOCKER();
  receiver->thread()->eventLoop()->postEvent(receiver, event);
}
