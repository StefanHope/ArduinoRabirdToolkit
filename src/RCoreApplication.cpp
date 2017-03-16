#include "RCoreApplication.h"
#include "REvent.h"
#include "REventLoop.h"
#include "RThread.h"
#include "RSpinLocker.h"
#include "RNullStream.h"
#include "RIsr.h"

static RCoreApplication *sApp = NULL;

RCoreApplication::RCoreApplication()
  : mNullStream(new RNullStream())
{
  R_MAKE_SPINLOCKER();

  sApp = this;
}

RCoreApplication::~RCoreApplication()
{
  _rIsrFinalize();
}

RNullStream *
RCoreApplication::nullStream()
{
  return mNullStream.data();
}

RCoreApplication *
RCoreApplication::instance()
{
  return sApp;
}

int
RCoreApplication::exec()
{
  return RThread::currentThread()->eventLoop()->exec();
}

void
RCoreApplication::processEvents()
{
  RThread::currentThread()->eventLoop()->processEvents();
}

void
RCoreApplication::postEvent(RObject *receiver, REvent *event)
{
  R_MAKE_SPINLOCKER();
  receiver->thread()->eventLoop()->postEvent(receiver, event);
}
