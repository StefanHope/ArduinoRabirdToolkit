#include "REvent.h"
#include "RAtomicInteger.h"

REvent::REvent(const rcount &type) : mType(type), mIsAccepted(false)
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
  return mType;
}

rcount
REvent::registerEventType()
{
  static RAtomicInteger<rcount> previousType = RNumericLimits<rcount>::sMax;

  // FIXME: If type value exceed the type size, we should report error!
  return previousType--;
}

REvent *
rMakeEvent(const rcount &type)
{
  return new REvent(type);
}
