#include "REventLoop.h"
#include "RThread.h"

static std::list<std::pair<TaskHandle_t, REventLoop *> >
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
  while(!mEvents.empty())
  {
    auto eventData = mEvents.front();
    mEvents.pop_front();

    eventData.receiver->event(eventData.event);

    // Free the posted event
    delete eventData.event;

    if(mIsInterrupt)
    {
      return false;
    }
  }

  return true;
}

REventLoop *
REventLoop::instance(const TaskHandle_t handle)
{
  for(auto it = sThreadEventLoops.begin(); it != sThreadEventLoops.end(); ++it)
  {
    if(handle == it->first)
    {
      return it->second;
    }
  }

  // FIXME: Memory leaking without free!
  REventLoop *loop = new REventLoop();

  // FIXME: Thread event loops should be protected by mutexs.
  sThreadEventLoops.push_back(
    std::pair<TaskHandle_t, REventLoop *>(RThread::currentThreadId(), loop));

  return loop;
}

REventLoop *
REventLoop::instance()
{
  return instance(RThread::currentThreadId());
}

void
REventLoop::_destroy(const TaskHandle_t handle)
{
  for(auto it = sThreadEventLoops.begin(); it != sThreadEventLoops.end(); ++it)
  {
    if(handle == it->first)
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
