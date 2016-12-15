#include "REventLoop.h"
#include "RThread.h"

static std::list<REventLoop *>
sThreadEventLoops;

REventLoop::REventLoop() : mReturnCode(0), mIsInterrupt(false)
{
}

REventLoop::~REventLoop()
{
  clear();
}

int
REventLoop::exec()
{
  while(true)
  {
    RThread::yieldCurrentThread();

    if(!processEvents())
    {
      clear();
      return mReturnCode;
    }

    // TODO: Only check timers on idle.
  }
}

void
REventLoop::exit(int returnCode)
{
  mReturnCode  = returnCode;
  mIsInterrupt = true;
}

void
REventLoop::quit()
{
  exit(0);
}

bool
REventLoop::processEvents()
{
  bool result = true;

  while(!mEvents.empty())
  {
    auto eventData = mEvents.front();
    mEvents.pop_front();

    eventData.receiver->event(eventData.event);

    // Free the posted event
    delete eventData.event;

    if(mIsInterrupt)
    {
      result = false;
      goto LABEL_EXIT;
    }
  }

LABEL_EXIT:

  // TODO: Free all objects that marked as deleteLater

  return result;
}

REventLoop *
REventLoop::instance(const RThread *inThread)
{
  for(auto it = sThreadEventLoops.begin(); it != sThreadEventLoops.end(); ++it)
  {
    if(inThread == (*it)->thread())
    {
      return *it;
    }
  }

  // FIXME: Memory leaking without free!
  REventLoop *loop = new REventLoop();

  // FIXME: Thread event loops should be protected by mutexs.
  sThreadEventLoops.push_back(loop);

  return loop;
}

REventLoop *
REventLoop::instance()
{
  return instance(RThread::currentThread());
}

void
REventLoop::_destroy(const RThread *inThread)
{
  for(auto it = sThreadEventLoops.begin(); it != sThreadEventLoops.end(); ++it)
  {
    if(inThread == (*it)->thread())
    {
      sThreadEventLoops.erase(it);
      return;
    }
  }
}

void
REventLoop::postEvent(RObject *receiver, REvent *event)
{
  mEvents.push_back(EventData(receiver, event));
}

void
REventLoop::clear()
{
  for(auto it = mEvents.begin(); it != mEvents.end(); ++it)
  {
    delete it->event;
  }

  mEvents.clear();
}

bool
REventLoop::hasPendingEvents()
{
  return !mEvents.empty();
}
