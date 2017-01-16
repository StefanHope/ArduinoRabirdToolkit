#include "RCoreApplication.h"
#include "REvent.h"
#include "REventLoop.h"
#include "RThread.h"
#include "RSpinLocker.h"

static RCoreApplication *sApp = NULL;

RCoreApplication::RCoreApplication()
{
  R_MAKE_SPINLOCKER();
  sApp = this;
}

RCoreApplication::~RCoreApplication()
{
}

RCoreApplication *
RCoreApplication::instance()
{
  return sApp;
}

int
RCoreApplication::exec()
{
  return sApp->thread()->eventLoop()->exec();
}

void
RCoreApplication::processEvents()
{
  sApp->thread()->eventLoop()->processEvents();
}

void
RCoreApplication::postEvent(RObject *receiver, REvent *event)
{
  receiver->thread()->eventLoop()->postEvent(receiver, event);
}
