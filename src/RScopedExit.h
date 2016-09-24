#ifndef __INCLUDED_D484B6DA826E11E6AA6EA088B4D1658C
#define __INCLUDED_D484B6DA826E11E6AA6EA088B4D1658C

#include "RTypes.h"

template <class Functor>
class RScopedExit
{
public:
  RScopedExit(const Functor &functor)
    : mFunctor(const_cast<Functor *>(&functor))
  {
  }

  RScopedExit(const RScopedExit<Functor> &other)
    : mFunctor(other.mFunctor)
  {
    // FIXME: We have broken the whole world, dirty way...
    const_cast<RScopedExit<Functor> &>(other).mFunctor = NULL;
  }

  ~RScopedExit ()
  {
    if(mFunctor)
    {
      (*mFunctor)();
    }
  }

private:
  Functor *mFunctor;
};

template <class T>
RScopedExit<T>
rMakeScopedExit(const T &functor)
{
  return RScopedExit<T>(const_cast<T &>(functor));
}

#define _R_SCOPED_EXIT(lineNumber) \
  auto __rTempScopeExit##lineNumber = rMakeScopedExit([&]

#define R_SCOPED_EXIT_BEGIN _R_SCOPED_EXIT(__LINE__)
#define R_SCOPED_EXIT_END   );

#endif // __INCLUDED_D484B6DA826E11E6AA6EA088B4D1658C
