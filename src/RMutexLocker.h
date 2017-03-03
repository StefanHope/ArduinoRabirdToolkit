#ifndef __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C
#define __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C

#include "RTypes.h"

template <class T>
class RMutexLocker
{
public:
  RMutexLocker(T *mutex)
    : mMutex(mutex)
  {
    if(mMutex)
    {
      mMutex->lock();
    }
  }

  ~RMutexLocker()
  {
    if(mMutex)
    {
      mMutex->unlock();
    }
  }

private:
  T *mMutex;

  R_DISABLE_COPY(RMutexLocker)
};

#define _R_MAKE_MUTEXLOCKER(mutex, lineNumber) \
  RMutexLocker<RRemoveReference<decltype(*mutex)>::Type > \
               __rTempMutexLocker##lineNumber(mutex);

#define R_MAKE_MUTEXLOCKER(mutex) _R_MAKE_MUTEXLOCKER((mutex), __LINE__)

#endif // __INCLUDED_4D7C908880E611E6AA6EA088B4D1658C
