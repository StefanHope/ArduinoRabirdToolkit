#include "REventLoop.h"
#include "RThread.h"
#include "RSpinLocker.h"
#include "RCoRoutine.h"
#include "RRealtimeTimer.h"

static uint32_t sMaxExpiry = RNumericLimits<uint32_t>::sMax / 2;

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

  execTimerQueue();

  while(!mEvents.empty())
  {
    EventData eventData;

    execTimerQueue();

    {
      R_MAKE_SPINLOCKER();
      eventData = mEvents.front();
      mEvents.pop_front();
    }

    if(eventData.event->type() == REvent::DeferredDelete)
    {
      mDeferredObjects.push_back(eventData.receiver);
    }
    else if(eventData.event->type() == REvent::MetaCall)
    {
      static_cast<RMetaCallEvent *>(eventData.event)->slot()();
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
      execTimerQueue();

      auto ret   = (*it)->run();
      auto oldIt = it;

      ++it;

      // Detach coroutines if it's exited!
      if(ret >= PT_EXITED)
      {
        if((*oldIt)->type() == RCoRoutine::Detached)
        {
          delete *oldIt;
        }

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

void
REventLoop::execTimerQueue()
{
#if defined(R_OS_NONOS)

  if(mTimerQueue.size() <= 0)
  {
    return;
  }

  auto it = mTimerQueue.begin();

  if((it->expiry - millis()) > sMaxExpiry)
  {
    // Expired!
    auto item = *it;

    mTimerQueue.erase(it);

    // NOTICE: If we don't clear this iterator, it will erase again inside
    // startTimer(), that will lead program crash!
    item.timer->mIt = mTimerQueue.end();

    if(item.timer->_isRestartFromCallback())
    {
      item.timer->run();

      if(!item.timer->isSingleShot())
      {
        startTimer(item.timer);   // Restart timer for next round
      }
    }
    else
    {
      // Do restart action inside event loop
      item.timer->_redirectEvents();
    }
  }

#endif // #if defined(R_OS_NONOS)
}

#if defined(R_OS_NONOS)
void
REventLoop::startTimer(RRealtimeTimer *timer)
{
  RTimerQueueItem item;

  item.timer  = timer;
  item.expiry = static_cast<uint32_t>(
    millis() + static_cast<unsigned long>(timer->interval()));

  if(timer->mIt != mTimerQueue.end())
  {
    mTimerQueue.erase(timer->mIt);
  }

  for(auto it = mTimerQueue.begin(); it != mTimerQueue.end(); ++it)
  {
    if((item.expiry - it->expiry) <= sMaxExpiry)
    {
      // Expiry after it->expiry
      continue;
    }

    mTimerQueue.insert(it, item);
    timer->mIt = --it;
    return;
  }

  // Can't found any place to insert, append to the end.
  mTimerQueue.push_back(item);
  timer->mIt = --mTimerQueue.end();
}

void
REventLoop::stopTimer(RRealtimeTimer *timer)
{
  if(timer->mIt != mTimerQueue.end())
  {
    mTimerQueue.erase(timer->mIt);
    timer->mIt = mTimerQueue.end();
  }
}

#endif // #if defined(R_OS_NONOS)
