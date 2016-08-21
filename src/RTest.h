#ifndef __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C
#define __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C

#include "RTypes.h"
#include "RObject.h"
#include <list>
#include <Print.h>

class RTest : public RObject
{
public:
  RTest(const class __FlashStringHelper *aName);

  enum Status
  {
    Passed = 0,
    Failed,
  };

  virtual void
  run() = 0;

  Status
  status();
  const class __FlashStringHelper *
    name();

protected:
  void
  setStatus(Status aStatus);

private:
  Status mStatus;
  const __FlashStringHelper *mName;
};

class RTestApplication : public RObject
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

private:
  // Static statistics for tests
  size_t mPassed;
  size_t mFailed;
  std::list<RTest *> mTests;
  Print *mPrint;
};

#endif // __INCLUDED_AE64810C67B511E6AA6EA088B4D1658C
