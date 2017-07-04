#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RUniquePointer.h"
#include "RPreprocessor.h"
#include "RCpuTimer.h"
#include <pt/pt.h>

#define RCR_WAIT_UNITL(condition)  PT_WAIT_UNTIL(&this->mPt, (condition))
#define RCR_WAIT_WHILE(condition)  PT_WAIT_WHILE(&this->mPt, (condition))
#define RCR_YIELD()                PT_YIELD(&this->mPt)
#define RCR_YIELD_UNTIL(condition) PT_YIELD_UNTIL(&this->mPt, (condition))
#define RCR_EXIT()                 PT_EXIT(&this->mPt)
#define RCR_SLEEP(ms) \
  do { \
    pCpuTimer.start(); \
    RCR_WAIT_UNTIL(pCpuTimer.elapsed() > ms); \
  } while(0)
#define RCR_SPAWN(className, ...) \
  RCoRoutineSpawner<className>::spawn( \
    rThis \
    RPP_IF_ARGS_NOT_EMPTY(RPP_COMMA, __VA_ARGS__)() \
    __VA_ARGS__)
#define RCR_SPAWN_DETACHED(className, ...) \
  RCoRoutineSpawner<className>::spawnDetached( \
    rThis \
    RPP_IF_ARGS_NOT_EMPTY(RPP_COMMA, __VA_ARGS__)() \
    __VA_ARGS__)
#define RCR_WAIT_CR(otherCR) \
  PT_WAIT_THREAD((&this->mPt), (otherCR)->run())

#define RCR_BEGIN(implClassName, crName, ...) \
  class crName : public RCoRoutineImpl<implClassName> \
  { \
public: \
    RCpuTimer pCpuTimer; \
    RPP_ARGUMENTS_EXTRACT(RPP_EMPTY, RPP_CLASS_MEMBER, __VA_ARGS__) \
    crName(implClassName * impl \
           RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_ARGUMENT, __VA_ARGS__)) \
      : RCoRoutineImpl<implClassName>(impl) \
      RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_INIT_LIST, __VA_ARGS__) \
    { \
    } \
public:
#define RCR_IMPL() \
  char run() \
  { if(_isTerminated()) {return PT_EXITED; }; \
    PT_BEGIN(&this->mPt);

#define RCR_END() PT_END(&this->mPt); } };

class RCoRoutine : public RObject
{
public:
  enum Type
  {
    Attached,
    Detached,
  };

  RCoRoutine(void *impl);

  ~RCoRoutine();

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
  int8_t      mType : 2;
};

template <class ImplementationType>
class RCoRoutineImpl : public RCoRoutine
{
protected:
  RCoRoutineImpl(ImplementationType *impl) : RCoRoutine(impl)
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
    return RUniquePointer<T>(new T(params ...));
  }

  template <class ... ParamTypes>
  static void
  spawnDetached(ParamTypes ... params)
  {
    auto cr = new T(params ...);

    cr->setType(RCoRoutine::Detached);
  }
};

#endif // __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
