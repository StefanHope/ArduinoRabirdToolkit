#include "RCoRoutine.h"
#include "RThread.h"
#include "REventLoop.h"

RBasicCoRoutine::RBasicCoRoutine(void *impl) : mImpl(impl), mType(Attached)
{
  PT_INIT(&mPt);
  thread()->eventLoop()->_attachCR(this);
}

RBasicCoRoutine::~RBasicCoRoutine()
{
  // Detached coroutines will be remove automatically while coroutine finished.
  if(type() == Attached)
  {
    thread()->eventLoop()->_detachCR(this);
  }
}

void
RBasicCoRoutine::setType(RBasicCoRoutine::Type aType)
{
  mType = aType;
}

RBasicCoRoutine::Type
RBasicCoRoutine::type()
{
  return static_cast<Type>(mType);
}

void
RBasicCoRoutine::terminate()
{
  PT_INIT(&mPt);
  mIsTerminated = true;
}

bool
RBasicCoRoutine::_isTerminated()
{
  return mIsTerminated;
}
