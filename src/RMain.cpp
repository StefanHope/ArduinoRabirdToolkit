#include "RMain.h"
#include "RTypes.h"
#include "RThread.h"
#include "RCoreApplication.h"

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

    sMainThread = RThread::currentThread();

    rMain(1, argv);
  }

  if(rCoreApp)
  {
    rCoreApp->processEvents();
  }
}
