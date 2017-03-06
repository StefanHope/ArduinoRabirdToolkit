#include "RObject.h"
#include "RThread.h"
#include "REvent.h"

RObject::RObject(RThread *targetThread)
  : mThread(targetThread)
{
}

RObject::RObject()
  : mThread(RThread::currentThread())
{
}

RObject::~RObject()
{
}

size_t
RObject::printTo(Print&p) const
{
  size_t size = 0;

  size += p.print(F("RObject(0x"));
  size += p.print(
    static_cast<uintptr_t>(reinterpret_cast<int>(this)), HEX);
  size += p.print(F(")"));

  return size;
}

bool
RObject::event(REvent *e)
{
  // TODO: We need to dispatch some common events
  return false;
}

RThread *
RObject::thread() const
{
  return mThread.data();
}

void
RObject::moveToThread(RThread *targetThread)
{
  mThread.reset(targetThread);
}
