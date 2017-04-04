#include "RCoRoutine.h"
#include "RThread.h"
#include "REventLoop.h"

RCoRoutine::~RCoRoutine()
{
  // We should detach this CR if we be destroied.
  thread()->eventLoop()->_detachCR(this);
}

void
RCoRoutine::terminate()
{
  // run() will return PT_ENDED lead REventLoop detach this CR.
  mRunner.reset();
}

char
RCoRoutine::run()
{
  if(!mRunner)
  {
    return PT_ENDED;
  }

  return mRunner->run();
}

void
RCoRoutine::_attachThisToEventLoop()
{
  thread()->eventLoop()->_attachCR(this);
}
