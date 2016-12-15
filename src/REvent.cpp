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

int
REvent::type() const
{
  return 0;
}

int
REvent::registerEventType()
{
  static RAtomicInteger<int> previousType = 0;

  return ++previousType;
}
