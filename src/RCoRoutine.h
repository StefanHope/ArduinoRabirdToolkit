#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RUniquePointer.h"
#include "RPreprocessor.h"
#include "RCpuTimer.h"
#include <pt/pt.h>

#define RCR_WAIT_UNTIL(condition)  PT_WAIT_UNTIL(&this->mPt, (condition))
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
  rSpawn##className( \
    rThis \
    RPP_IF_ARGS_NOT_EMPTY(RPP_COMMA, __VA_ARGS__)() \
    __VA_ARGS__)
#define RCR_SPAWN_DETACHED(className, ...) \
  rSpawnDetached##className( \
    rThis \
    RPP_IF_ARGS_NOT_EMPTY(RPP_COMMA, __VA_ARGS__)() \
    __VA_ARGS__)
#define RCR_WAIT_CR(otherCR) \
  PT_WAIT_THREAD((&this->mPt), (otherCR)->run())

#define RCRR_PP_ASSIGN_VARS(r, data, elem) \
  BOOST_PP_CAT(self->a, BOOST_PP_TUPLE_ELEM(1, elem)) = \
    BOOST_PP_CAT(in, BOOST_PP_TUPLE_ELEM(1, elem));

#define RCR_DECLARE(crName, implClassName, ...) \
  class crName; \
  extern RUniquePointer<crName> rSpawn##crName( \
    implClassName * impl \
    RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_ARGUMENT, __VA_ARGS__)); \
  extern void rSpawnDetached##crName( \
    implClassName * impl \
    RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_ARGUMENT, __VA_ARGS__));

#define RCR_BEGIN(crName, implClassName, ...) \
  class crName : public RCoRoutineImpl<implClassName> \
  { \
public: \
    RCpuTimer pCpuTimer; \
    RPP_ARGUMENTS_EXTRACT(RPP_EMPTY, RPP_CLASS_MEMBER, __VA_ARGS__) \
    crName(implClassName * impl) \
      : RCoRoutineImpl<implClassName>(impl) \
    { \
    } \
    ~crName() \
    { \
    } \
    char run(); \
public:
#define RCR_IMPL(crName, implClassName, ...) \
  }; \
  RUniquePointer<crName> rSpawn##crName( \
    implClassName * impl \
    RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_ARGUMENT, __VA_ARGS__)) \
  { \
    RUniquePointer<crName> self(new crName(impl)); \
    RPP_ARGUMENTS_EXTRACT(RPP_EMPTY, RCRR_PP_ASSIGN_VARS, __VA_ARGS__); \
    return self; \
  } \
  void rSpawnDetached##crName( \
    implClassName * impl \
    RPP_ARGUMENTS_EXTRACT(RPP_COMMA, RPP_FUNC_ARGUMENT, __VA_ARGS__)) \
  { \
    auto self(new crName(impl)); \
    self->setType(RCoRoutine::Detached); \
    RPP_ARGUMENTS_EXTRACT(RPP_EMPTY, RCRR_PP_ASSIGN_VARS, __VA_ARGS__); \
  } \
  char crName::run() \
  { \
    if(_isTerminated()) \
    { \
      return PT_EXITED; \
    } \
    PT_BEGIN(&this->mPt);

#define RCR_END() PT_END(&this->mPt); }

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

#endif // __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
