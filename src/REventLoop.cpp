#include "REventLoop.h"
#include "RThread.h"
#include "RSpinLocker.h"
#include "RCoRoutine.h"

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
    EventData eventData;

    {
      R_MAKE_SPINLOCKER();
      eventData = mEvents.front();
      mEvents.pop_front();
    }

    if(eventData.event->type() == REvent::DeferredDelete)
    {
      mDeferredObjects.push_back(eventData.receiver);
    }
    else
    {
      eventData.receiver->event(eventData.event);
    }

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
  if(mDeferredObjects.size() > 0)
  {
    for(auto it = mDeferredObjects.begin(); it != mDeferredObjects.end(); ++it)
    {
      delete *it;
    }

    mDeferredObjects.clear();
  }

  // Schedule coroutines
  if(mCoRoutines.size() > 0)
  {
    for(auto it = mCoRoutines.begin(); it != mCoRoutines.end(); )
    {
      auto ret   = (*it)->run();
      auto oldIt = it;

      ++it;

      // Detach coroutines if it's exited!
      if(ret >= PT_EXITED)
      {
        mCoRoutines.erase(oldIt);
      }
    }
  }

  idle.emit();

  // Give control to other threads.
  RThread::yieldCurrentThread();

  return result;
}

void
REventLoop::_attachCR(RCoRoutine *cr)
{
  if((NULL == cr) || (cr->thread()->id() != thread()->id()))
  {
    /* Don't put invalid coroutine into list */
    return;
  }

  mCoRoutines.remove(cr);
  mCoRoutines.push_back(cr);
}

void
REventLoop::_detachCR(RCoRoutine *cr)
{
  mCoRoutines.remove(cr);
}

void
REventLoop::postEvent(RObject *receiver, REvent *event)
{
  R_MAKE_SPINLOCKER();
  mEvents.push_back(EventData(receiver, event));
}

void
REventLoop::clear()
{
  R_MAKE_SPINLOCKER();

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
