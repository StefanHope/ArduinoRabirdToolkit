#include "RCoreApplication.h"
#include "REventLoop.h"

static RCoreApplication *sApplication = NULL;

RCoreApplication::RCoreApplication()
{
  sApplication = this;
}

RCoreApplication *
RCoreApplication::instance()
{
  return sApplication;
}

int
RCoreApplication::exec()
{
  REventLoop *loop = REventLoop::instance();

  return loop->exec();
}
