#include "RCoRoutine.h"
#include "RThread.h"
#include "REventLoop.h"

RCoRoutine::RCoRoutine(void *impl) : mImpl(impl), mType(Attached)
{
  PT_INIT(&mPt);
  thread()->eventLoop()->_attachCR(this);
}

RCoRoutine::~RCoRoutine()
{
  // Detached coroutines will be remove automatically while coroutine finished.
  if(type() == Attached)
  {
    thread()->eventLoop()->_detachCR(this);
  }
}

void
RCoRoutine::setType(RCoRoutine::Type aType)
{
  mType = aType;
}

RCoRoutine::Type
RCoRoutine::type()
{
  return static_cast<Type>(mType);
}

void
RCoRoutine::terminate()
{
  PT_INIT(&mPt);
  mIsTerminated = true;
}

bool
RCoRoutine::_isTerminated()
{
  return mIsTerminated;
}
