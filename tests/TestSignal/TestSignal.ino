# 2 "TestSignal.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RTest.h>
#include <RSignal.h>

static int sVar0           = 0x1;
static int sVar1           = 0x2;
static int sVar2           = 0x3;
static int sExecutedCount0 = 0;
static int sExecutedCount1 = 0;
static int sExecutedCount2 = 0;

class AClass
{
public:
  AClass() : mVar0(0x4)
  {
  }

  void
  signalClassMethod0()
  {
    mVar0 = 0xAD;
  }

  int mVar0;
};

void
signalFunction0()
{
  sVar0 = 0xEB;
  ++sExecutedCount0;
}

void
signalFunction1(int var1)
{
  sVar1 = var1;
  ++sExecutedCount1;
}

void
signalFunction2(int var1, int var2)
{
  sVar1 = var1;
  sVar2 = var2;
  ++sExecutedCount2;
}

RTEST(TestSignal)
{
  AClass a;

  RSignal<void()>         signal0;
  RSignal<void(int)>      signal1;
  RSignal<void(int, int)> signal2;
  RSignal<void()>         signal3;

  RASSERT_EQUAL(sVar0, 0x1);
  RASSERT_EQUAL(sVar1, 0x2);
  RASSERT_EQUAL(sVar2, 0x3);
  RASSERT_EQUAL(sExecutedCount0, 0);
  RASSERT_EQUAL(sExecutedCount1, 0);
  RASSERT_EQUAL(sExecutedCount2, 0);

  signal0.connect(signalFunction0);
  RASSERT_EQUAL(sVar0, 0x1);
  signal0.emit();
  RASSERT_EQUAL(sVar0, 0xEB);
  RASSERT_EQUAL(sExecutedCount0, 1);

  signal1.connect(signalFunction1);
  RASSERT_EQUAL(sVar1, 0x2);
  signal1.emit(0xCA);
  RASSERT_EQUAL(sVar1, 0xCA);
  RASSERT_EQUAL(sExecutedCount1, 1);

  signal2.connect(signalFunction2);
  RASSERT_EQUAL(sVar1, 0xCA);
  RASSERT_EQUAL(sVar2, 0x3);
  signal2.emit(0xCA, 0x7B);
  RASSERT_EQUAL(sVar1, 0xCA);
  RASSERT_EQUAL(sVar2, 0x7B);
  RASSERT_EQUAL(sExecutedCount2, 1);

  signal2.emit(0x2C, 0x3B);
  RASSERT_EQUAL(sVar1, 0x2C);
  RASSERT_EQUAL(sVar2, 0x3B);
  RASSERT_EQUAL(sExecutedCount2, 2);

  signal3.connect(&a, &AClass::signalClassMethod0);
  RASSERT_EQUAL(a.mVar0, 0x4);
  signal3.emit();
  RASSERT_EQUAL(a.mVar0, 0xAD);
};

void
setup()
{
  Serial.begin(9600);

  while(!Serial)  // for the Arduino Leonardo/Micro only
  {
  }

  RTestApplication testApp;

  testApp.addTest(&RTEST_INSTANCE(TestSignal));
  testApp.run();
}

void
loop()
{
}
