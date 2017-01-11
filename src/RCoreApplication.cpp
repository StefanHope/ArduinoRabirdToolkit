#include "RCoreApplication.h"
#include "REvent.h"
#include "REventLoop.h"
#include "RThread.h"

static RCoreApplication *sApplication = NULL;

RCoreApplication::RCoreApplication()
  : mEventLoop(NULL)
{
  sApplication = this;
  mEventLoop   = REventLoop::instance();
}

RCoreApplication::~RCoreApplication()
{
}

RCoreApplication *
RCoreApplication::instance()
{
  return sApplication;
}

int
RCoreApplication::exec()
{
  return sApplication->mEventLoop->exec();
}

void
RCoreApplication::processEvents()
{
  sApplication->mEventLoop->processEvents();
}

void
RCoreApplication::postEvent(RObject *receiver, REvent *event)
{
  REventLoop::instance(receiver->thread())->postEvent(receiver, event);
}
