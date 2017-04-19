#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RUniquePointer.h"
#include <pt/pt.h>

#define RCR_BEGIN() \
  if(_isTerminated()) {return PT_EXITED; }; \
  PT_BEGIN(&this->mPt)
#define RCR_END()                  PT_END(&this->mPt)
#define RCR_WAIT_UNITL(condition)  PT_WAIT_UNTIL(&this->mPt, (condition))
#define RCR_WAIT_WHILE(condition)  PT_WAIT_WHILE(&this->mPt, (condition))
#define RCR_YIELD()                PT_YIELD(&this->mPt)
#define RCR_YIELD_UNTIL(condition) PT_YIELD_UNTIL(&this->mPt, (condition))
#define RCR_EXIT()                 PT_EXIT(&this->mPt)
#define RCR_SPAWN(className, ...) \
  RCoRoutineSpawner<className>::spawn(rThis, __VA_ARGS__)
#define RCR_SPAWN_DETACHED(className, ...) \
  RCoRoutineSpawner<className>::spawnDetached(rThis, __VA_ARGS__)
#define RCR_WAIT_CR(otherCR) \
  PT_WAIT_THREAD((&this->mPt), (otherCR)->run())

class RBasicCoRoutine : public RObject
{
public:
  enum Type
  {
    Attached,
    Detached,
  };

  RBasicCoRoutine(void *impl);

  ~RBasicCoRoutine();

  void
  setType(Type aType);

  Type
  type();

  virtual char
  run() = 0;

  void
  terminate();

protected:
  void *
  _impl()
  {
    return const_cast<void *>(mImpl);
  }

  bool
  _isTerminated();

public:
  struct pt mPt;

private:
  const void *mImpl;
  int8_t      mType         : 2;
  bool        mIsTerminated : 1;
};

template <class ImplementationType>
class RCoRoutine : public RBasicCoRoutine
{
protected:
  RCoRoutine(ImplementationType *impl) : RBasicCoRoutine(impl)
  {
  }

  // Provided rThis support
  inline ImplementationType *
  pImpl()
  {
    return static_cast<ImplementationType *>(_impl());
  }

  inline ImplementationType *
  pImpl() const
  {
    return static_cast<ImplementationType *>(_impl());
  }
};

template <class T>
class RCoRoutineSpawner
{
public:
  template <class ... ParamTypes>
  static RUniquePointer<T>
  spawn(ParamTypes ... params)
  {
    return new T(params ...);
  }

  template <class ... ParamTypes>
  static void
  spawnDetached(ParamTypes ... params)
  {
    auto cr = new T(params ...);

    cr->setType(RBasicCoRoutine::Detached);
  }
};

#endif // __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
