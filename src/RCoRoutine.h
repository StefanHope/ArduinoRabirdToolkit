#ifndef __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C
#define __INCLUDED_82D14FF80A1611E7AA6EA088B4D1658C

#include "RObject.h"
#include "RUniquePointer.h"
#include <pt/pt.h>
#include <boost/preprocessor.hpp>

#define RCR_IMPL_BEGIN() \
  if(_isTerminated()) {return PT_EXITED; }; \
  PT_BEGIN(&this->mPt)
#define RCR_IMPL_END()             PT_END(&this->mPt)
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

#define RCR_PP_EMPTY(...)

#define RCR_PP_ARGUMENT_CLASS_DECL(r, data, elem) \
  BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_CAT(a, BOOST_PP_TUPLE_ELEM(1, elem));

#define RCR_PP_ARGUMENT_FUNC_DECL(r, data, elem) \
  BOOST_PP_TUPLE_ELEM(0, elem) BOOST_PP_CAT(in, BOOST_PP_TUPLE_ELEM(1, elem)) \
  BOOST_PP_COMMA_IF(BOOST_PP_SUB(data, BOOST_PP_DEC(r)))

#define RCR_PP_ARGUMENT_FUNC_IMPL(r, data, elem) \
  BOOST_PP_IF(BOOST_PP_SUB(r, 2), BOOST_PP_EMPTY, BOOST_PP_COMMA)() \
  BOOST_PP_CAT(a, BOOST_PP_TUPLE_ELEM(1, elem))( \
    BOOST_PP_CAT(in, BOOST_PP_TUPLE_ELEM(1, elem))) \
  BOOST_PP_COMMA_IF(BOOST_PP_SUB(data, BOOST_PP_DEC(r)))

#define RCR_PP_ARGUMENTS_FOR_EACH(macro, seq) \
  BOOST_PP_SEQ_FOR_EACH( \
    macro, \
    BOOST_PP_SEQ_SIZE(seq), \
    seq)

#define RCR_PP_ARGUMENTS_EXPAND(macro, ...) \
  BOOST_PP_IF( \
    BOOST_PP_IS_EMPTY(__VA_ARGS__), \
    RCR_PP_EMPTY, \
    RCR_PP_ARGUMENTS_FOR_EACH)(macro, BOOST_PP_TUPLE_TO_SEQ((__VA_ARGS__)))

#define RCR_BEGIN(implClassName, crName, ...) \
  class crName : public RCoRoutineImpl<implClassName> \
  { \
public: \
    RCR_PP_ARGUMENTS_EXPAND(RCR_PP_ARGUMENT_CLASS_DECL, __VA_ARGS__) \
    crName( \
      implClassName * impl, \
      RCR_PP_ARGUMENTS_EXPAND(RCR_PP_ARGUMENT_FUNC_DECL, __VA_ARGS__)) \
      : RCoRoutineImpl<implClassName>(impl) \
      RCR_PP_ARGUMENTS_EXPAND(RCR_PP_ARGUMENT_FUNC_IMPL, __VA_ARGS__) \
    { \
    }; \
public:
#define RCR_IMPL() \
  char run() \
  { RCR_IMPL_BEGIN();

#define RCR_END() RCR_IMPL_END(); }; };

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
    return new T(params ...);
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
