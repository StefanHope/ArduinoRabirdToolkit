#ifndef __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C
#define __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C

#include "RTypes.h"
#include "RObject.h"
#include <list>
#include <Print.h>

// helper define for the operators below
#define RASSERT_OP(arg1, op, opName, arg2) \
  if(!assertion<decltype(arg2)>( \
       F(__FILE__), __LINE__, F(#arg1), (arg1), F(opName), op, F(#arg2), \
       (arg2))) \
  { \
    return; \
  };

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

class RTest;
class RTestApplication;

class RTestAbstractApplication : public RObject
{
protected:
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
  RTest(const class __FlashStringHelper *aName);

  virtual void
  run() = 0;

  Status
  status();

  const __FlashStringHelper *
  name();

  /** Template binary operator== to assist with assertions */
  template <typename T>
  static bool
  isEqual(const T&a, const T&b)
  {
    return a == b;
  }

  /** Template binary operator!= to assist with assertions */
  template <typename T>
  static bool
  isNotEqual(const T&a, const T&b)
  {
    return !(a == b);
  }

  /** Template binary operator< to assist with assertions */
  template <typename T>
  static bool
  isLess(const T&a, const T&b)
  {
    return a < b;
  }

  /** Template binary operator> to assist with assertions */
  template <typename T>
  static bool
  isMore(const T&a, const T&b)
  {
    return b < a;
  }

  /** Template binary operator<= to assist with assertions */
  template <typename T>
  static bool
  isLessOrEqual(const T&a, const T&b)
  {
    return !(b < a);
  }

  /** Template binary operator>= to assist with assertions */
  template <typename T>
  static bool
  isMoreOrEqual(const T&a, const T&b)
  {
    return !(a < b);
  }

  template <class T>
  bool
  assertion(const __FlashStringHelper *file, uint16_t line,
            const __FlashStringHelper *lhss, const T&lhs,
            const __FlashStringHelper *ops, bool (*op)(const T&lhs,
                                                       const T&rhs), const __FlashStringHelper *rhss,
            const T&rhs)
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
    mManager->printer()->print(F("), file "));
    mManager->printer()->print(file);
    mManager->printer()->print(F(", line "));
    mManager->printer()->print(line);
    mManager->printer()->println(".");

    return ok;
  }

protected:
  void
  setStatus(Status aStatus);

  void
  setManager(RTestAbstractApplication *manager);

private:
  Status mStatus;
  const __FlashStringHelper *mName;
  RTestAbstractApplication * mManager;

  friend RTestApplication;
};

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isLess<const char *>(const char *const &a, const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isLessOrEqual<const char *>(const char *const &a, const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isEqual<const char *>(const char *const &a, const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isNotEqual<const char *>(const char *const &a, const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isMore<const char *>(const char *const &a, const char *const &b);

/** Template specialization for asserting const char * types */
template <>
bool
RTest::isMoreOrEqual<const char *>(const char *const &a, const char *const &b);

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

protected:
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
