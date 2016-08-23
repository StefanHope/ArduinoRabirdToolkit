# 2 "TestStringRefs.ino"

#include "BasicStringRef.h"
#include "BasicTestStringRef.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>
#include <RAbstractStringRef.h>
#include <RConstStringRef.h>
#include <RStringRef.h>
#include <RFlashStringRef.h>
#include <RTest.h>
#include <string.h>

class TestBasicStringRef
  : public BasicTestStringRef<TestBasicStringRef, BasicStringRef>
{
public:
  typedef BasicStringRef                                        StringRefType;
  typedef BasicTestStringRef<TestBasicStringRef, StringRefType> BaseType;

  TestBasicStringRef()

    : BaseType(F("TestBasicStringRef"))
    , mStringRef0(mNormalString0)
    , mStringRef1(mNormalString1)
    , mStringRef2(mNormalString2)
    , mStringRef3(mNormalString3)
    , mStringRef4(mNormalString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
};

class TestConstStringRef
  : public BasicTestStringRef<TestConstStringRef, RConstStringRef>
{
public:
  typedef RConstStringRef
    StringRefType;
  typedef BasicTestStringRef<TestConstStringRef, RConstStringRef> BaseType;

  TestConstStringRef()

    : BaseType(F("TestConstStringRef"))
    , mStringRef0(mNormalString0)
    , mStringRef1(mNormalString1)
    , mStringRef2(mNormalString2)
    , mStringRef3(mNormalString3)
    , mStringRef4(mNormalString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
};

class TestFlashStringRef
  : public BasicTestStringRef<TestFlashStringRef, RFlashStringRef>
{
public:
  typedef RFlashStringRef                                       StringRefType;
  typedef BasicTestStringRef<TestFlashStringRef, StringRefType> BaseType;

  TestFlashStringRef()

    : BaseType(F("TestFlashStringRef"))
    , mStringRef0(mFlashString0)
    , mStringRef1(mFlashString1)
    , mStringRef2(mFlashString2)
    , mStringRef3(mFlashString3)
    , mStringRef4(mFlashString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
};

class TestStringRef
  : public BasicTestStringRef<TestStringRef, RStringRef>
{
public:
  typedef RStringRef                                       StringRefType;
  typedef BasicTestStringRef<TestStringRef, StringRefType> BaseType;

  TestStringRef()

    : BaseType(F("TestStringRef"))
    , mStringRef0(&mString0)
    , mStringRef1(&mString1)
    , mStringRef2(&mString2)
    , mStringRef3(&mString3)
    , mStringRef4(&mString4)
  {
  }

public:
  StringRefType mStringRef0;
  StringRefType mStringRef1;
  StringRefType mStringRef2;
  StringRefType mStringRef3;
  StringRefType mStringRef4;
};

void
setup()
{
  Serial.begin(9600);

  while(!Serial)  // for the Arduino Leonardo/Micro only
  {
  }

  RTestApplication   testApp;
  TestBasicStringRef testBasicStringRef;
  TestConstStringRef testConstStringRef;
  TestFlashStringRef testFlashStringRef;
  TestStringRef      testStringRef;

  testApp.addTest(&testBasicStringRef);
  testApp.addTest(&testConstStringRef);
  testApp.addTest(&testFlashStringRef);
  testApp.addTest(&testStringRef);
  testApp.run();
}

void
loop()
{
}
