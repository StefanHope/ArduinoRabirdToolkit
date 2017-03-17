#include "RCoRoutine.h"

R_IMPLEMENT_PRIVATE(RCoRoutine)

struct RCoRoutinePrivate
{
  struct pt mPt;
};

struct RCoRoutineImpl
{
};

RCoRoutine::RCoRoutine()
{
}

RCoRoutine::~RCoRoutine()
{
}

char
RCoRoutine::run()
{
}
