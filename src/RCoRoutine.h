#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RUniquePointer.h"
#include "RCoRoutineRunner.h"
#include "RSpinLocker.h"

#define RCR_BEGIN()                PT_BEGIN(&this->mPt)
#define RCR_END()                  PT_END(&this->mPt)
#define RCR_WAIT_UNITL(condition)  PT_WAIT_UNTIL(&this->mPt, (condition))
#define RCR_WAIT_WHILE(condition)  PT_WAIT_WHILE(&this->mPt, (condition))
#define RCR_YIELD()                PT_YIELD(&this->mPt)
#define RCR_YIELD_UNTIL(condition) PT_YIELD_UNTIL(&this->mPt, (condition))
#define RCR_EXIT()                 PT_EXIT(&this->mPt)
#define RCR_SPAWN(otherCR, args ...) \
  do { \
    if(!PT_SCHEDULE((otherCR)->spawn(args))) \
    { \
      return PT_WAITING; \
    } \
    PT_WAIT_THREAD((&this->mPt), (otherCR)->run()) \
  } while(0);

/**
 * @brief The RCoRoutine class
 *
 * CoRoutine design, not yet implemented.
 */
class RCoRoutine : public RObject
{
public:
  ~RCoRoutine();

  template <class T, class ... ParamTypes>
  char
  spawn(ParamTypes ... params)
  {
    { // CoRoutine won't run between different threads, but spinlock could
      // ensure memory allocation will always get the same memory block we just
      // free or not get heap space grow up.
      R_MAKE_SPINLOCKER();

      mRunner.reset();
      mRunner.reset(new T(params ...));
    }

    _attachThisToEventLoop();

    return PT_WAITING;
  }

  void
  terminate();

protected:
  char
  run();

private:
  void
  _attachThisToEventLoop();

private:
  friend class REventLoop;

  RUniquePointer<RCoRoutineRunner> mRunner;
};

#endif // __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
