#ifndef __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C
#define __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C

#include "RGlobal.h"
#include "RObject.h"
#include <list>
#include <Print.h>

// helper define for the operators below
#define RASSERT_OP(arg1, op, opName, arg2) \
  do \
  { \
    auto tempArg1 = (arg1); \
    auto tempArg2 = (arg2); \
    if(!assertion<decltype(tempArg1), decltype(tempArg2)>( \
         __LINE__, F(#arg1), (tempArg1), F(opName), op, F(#arg2), \
         (tempArg2))) \
    { \
      return; \
    }; \
  } while(false);

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_EQUAL(arg1, arg2) RASSERT_OP(arg1, isEqual, "==", arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_NOT_EQUAL(arg1, arg2) RASSERT_OP(arg1, isNotEqual, "!=", arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_LESS(arg1, arg2) RASSERT_OP(arg1, isLess, "<", arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_MORE(arg1, arg2) RASSERT_OP(arg1, isMore, ">", arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_LESS_OR_EQUAL(arg1, arg2) RASSERT_OP(arg1, isLessOrEqual, "<=", \
                                                     arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_MORE_OR_EQUAL(arg1, arg2) RASSERT_OP(arg1, isMoreOrEqual, ">=", \
                                                     arg2)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_TRUE(arg) RASSERT_EQUAL(arg, true)

/** macro generates optional output and calls fail() followed by a return if false. */
#define RASSERT_FALSE(arg) RASSERT_EQUAL(arg, false)

#define RTEST_INSTANCE(testName) s##testName
#define RTEST(testName)          class testName : public RTest \
{ \
public: \
    testName(); \
    void run(); \
}; \
  testName::testName() : RTest(F(#testName), F(__FILE__), __LINE__) \
  { \
  }; \
  static testName RTEST_INSTANCE(testName); \
  void testName::run()

class RTest;
class RTestApplication;

class RTestAbstractApplication : public RObject
{
public:
  virtual Print *
  printer() = 0;

private:
  friend RTest;
};

class RTest : public RObject
{
public:
  enum Status
  {
    Passed = 0,
    Failed,
  };

public:
  RTest(const rfchar *aName, const rfchar *fileName, int lineNo);

  virtual void
  run() = 0;

  Status
  status();

  const rfchar *
  name();
  const rfchar *
  fileName();

  int
  lineNo();

  /** Template binary operator== to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isEqual(const LeftType&a, const RightType&b)
  {
    return a == b;
  }

  /** Template binary operator!= to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isNotEqual(const LeftType&a, const RightType&b)
  {
    return !(a == b);
  }

  /** Template binary operator< to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isLess(const LeftType&a, const RightType&b)
  {
    return a < b;
  }

  /** Template binary operator> to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isMore(const LeftType&a, const RightType&b)
  {
    return b < a;
  }

  /** Template binary operator<= to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isLessOrEqual(const LeftType&a, const RightType&b)
  {
    return !(b < a);
  }

  /** Template binary operator>= to assist with assertions */
  template <class LeftType, class RightType>
  static bool
  isMoreOrEqual(const LeftType&a, const RightType&b)
  {
    return !(a < b);
  }

  template <class LeftType, class RightType>
  bool
  assertion(uint16_t line, const rfchar *lhss, const LeftType &lhs,
            const rfchar *ops, bool (*op)(
              const LeftType&lhs,
              const RightType&rhs), const rfchar *rhss, const RightType&rhs)
  {
    bool ok = op(lhs, rhs);

    if(!ok)
    {
      setStatus(RTest::Failed);
    }

    mManager->printer()->print(F("Assertion "));
    mManager->printer()->print(ok ? F("passed") : F("failed"));
    mManager->printer()->print(F(": ("));
    mManager->printer()->print(lhss);
    mManager->printer()->print(F("="));
    mManager->printer()->print(lhs);
    mManager->printer()->print(F(") "));
    mManager->printer()->print(ops);
    mManager->printer()->print(F(" ("));
    mManager->printer()->print(rhss);
    mManager->printer()->print(F("="));
    mManager->printer()->print(rhs);
    mManager->printer()->print(F("), line "));
    mManager->printer()->print(line);
    mManager->printer()->println(F("."));

    return ok;
  }

protected:
  void
  setStatus(Status status);

  void
  setManager(RTestAbstractApplication *manager);

  RTestAbstractApplication *
  manager();

private:
  Status        mStatus;
  const rfchar *mName;
  const rfchar *mFileName;
  const int     mLineNo;
  RTestAbstractApplication *mManager;

  friend RTestApplication;
};

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isLess<const char *, const char *>(const char *const &a,
                                          const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isLessOrEqual<const char *, const char *>(const char *const &a,
                                                 const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isEqual<const char *, const char *>(const char *const &a,
                                           const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isNotEqual<const char *, const char *>(const char *const &a,
                                              const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isMore<const char *, const char *>(const char *const &a,
                                          const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isMoreOrEqual<const char *, const char *>(const char *const &a,
                                                 const char *const &b);

class RTestApplication : public RTestAbstractApplication
{
public:
  RTestApplication();
  ~RTestApplication();

  Print *
  setOutput(Print *aPrint);

  void
  addTest(RTest *test);
  void
  run();

  Print *
  printer();

private:
  // Static statistics for tests
  size_t mPassed;
  size_t mFailed;

  std::list<RTest *> mTests;
  Print *mPrint;

  friend RTest;
};

#endif // __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C
