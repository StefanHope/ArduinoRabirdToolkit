#include "RObject.h"
#include "RThread.h"
#include "REvent.h"
#include "RCoreApplication.h"

RObject::RObject(RThread *targetThread)
#if !defined(R_OS_NONOS)
  : mThread(targetThread)
#endif
{
}

RObject::RObject()
#if !defined(R_OS_NONOS)
  : mThread(RThread::currentThread())
#endif
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
#if defined(R_OS_NONOS)
  return RThread::currentThread();
#else
  return mThread.data();
#endif
}

void
RObject::moveToThread(RThread *targetThread)
{
#if !defined(R_OS_NONOS)
  mThread.reset(targetThread);
#endif
}

void
RObject::deleteLater()
{
  RCoreApplication::postEvent(this,
                              rMakeEvent<REvent, REvent::DeferredDelete>());
}
