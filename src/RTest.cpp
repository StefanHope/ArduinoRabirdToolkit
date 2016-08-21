#include "RTest.h"
#include <Arduino.h>

RTest::RTest(const __FlashStringHelper *aName)
  : mStatus(Failed), mName(aName)
{
}

RTest::Status
RTest::status()
{
  return mStatus;
}

const __FlashStringHelper *
RTest::name()
{
  return mName;
}

void
RTest::setStatus(RTest::Status aStatus)
{
  mStatus = aStatus;
}

RTestApplication::RTestApplication()
  : mPassed(0), mFailed(0), mPrint(&Serial)
{
}

RTestApplication::~RTestApplication()
{
}

Print *
RTestApplication::setOutput(Print *aPrint)
{
  Print *oldPrint = mPrint;

  if(NULL == aPrint)
  {
    return oldPrint;
  }

  mPrint = aPrint;
  return oldPrint;
}

void
RTestApplication::addTest(RTest *test)
{
  if(NULL == test)
  {
    return;
  }

  mTests.push_back(test);
}

void
RTestApplication::run()
{
  auto it = mTests.begin();

  for(; it != mTests.end(); ++it)
  {
    (*it)->run();

    RTest::Status status = (*it)->status();
    const __FlashStringHelper *statusPrefix = F("UNKNOWN ");

    if(RTest::Passed == status)
    {
      ++mPassed;
      statusPrefix = F("PASSED  ");
    }
    else if(RTest::Failed == status)
    {
      ++mFailed;
      statusPrefix = F("FAILED  ");
    }

    mPrint->print(statusPrefix);
    mPrint->print(F(": "));
    mPrint->print((*it)->name());
    mPrint->println();
  }

  mPrint->print(F("Totals: "));
  mPrint->print(mPassed);
  mPrint->print(F(" passed, "));
  mPrint->print(mFailed);
  mPrint->print(F(" failed"));
  mPrint->println();
}
