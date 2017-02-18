#include "REvent.h"
#include "RAtomicInteger.h"

REvent::REvent()
{
}

REvent::~REvent()
{
}

void
REvent::accept()
{
  setAccepted(true);
}

void
REvent::ignore()
{
  setAccepted(false);
}

bool
REvent::isAccepted() const
{
  return mIsAccepted;
}

void
REvent::setAccepted(bool accepted)
{
  mIsAccepted = accepted;
}

rcount
REvent::type() const
{
  return 0;
}

rcount
REvent::registerEventType()
{
  static RAtomicInteger<rcount> previousType = 0;

  // FIXME: If type value exceed the type size, we should report error!
  return ++previousType;
}
