# 2 "TestSignal.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RTest.h>
#include <RSignal.h>

static int sVar0 = 0x1;
static int sVar1 = 0x2;
static int sVar2 = 0x3;

void
signalFunction0()
{
  sVar0 = 0xEB;
}

void
signalFunction1(int var1)
{
  sVar1 = var1;
}

void
signalFunction2(int var1, int var2)
{
  sVar1 = var1;
  sVar2 = var2;
}

RTEST(TestSignal)
{
  RSignal<void()>         signal0;
  RSignal<void(int)>      signal1;
  RSignal<void(int, int)> signal2;

  RASSERT_EQUAL(sVar0, 0x1);
  RASSERT_EQUAL(sVar1, 0x2);
  RASSERT_EQUAL(sVar2, 0x3);

  signal0.connect(signalFunction0);
  RASSERT_EQUAL(sVar0, 0x1);
  signal0.emit();
  RASSERT_EQUAL(sVar0, 0xEB);

  signal1.connect(signalFunction1);
  RASSERT_EQUAL(sVar1, 0x2);
  signal1.emit(0xCA);
  RASSERT_EQUAL(sVar1, 0xCA);

  signal2.connect(signalFunction2);
  RASSERT_EQUAL(sVar1, 0xCA);
  RASSERT_EQUAL(sVar2, 0x3);
  signal2.emit(0xCA, 0x7B);
  RASSERT_EQUAL(sVar1, 0xCA);
  RASSERT_EQUAL(sVar2, 0x7B);
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
