#include "RCoRoutineRunner.h"
#include "RCoRoutine.h"

RCoRoutineBasicRunner::RCoRoutineBasicRunner(void *impl) : mImpl(impl)
{
  PT_INIT(&mPt);
}

RCoRoutineBasicRunner::~RCoRoutineBasicRunner()
{
}
