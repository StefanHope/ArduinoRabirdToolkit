#include "RCoRoutine.h"
#include "RThread.h"
#include "REventLoop.h"
#include "RLimits.h"

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
  mPt.lc = RNumericLimits<R_RAW_TYPE_OF(mPt.lc)>::sMax;
}

bool
RCoRoutine::_isTerminated()
{
  return (RNumericLimits<R_RAW_TYPE_OF(mPt.lc)>::sMax == mPt.lc);
}

class A : public RObject
{
public:
};

RCR_BEGIN(A, rcTest, (int, Var))
RCR_IMPL()
RCR_END()
