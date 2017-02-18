# 2 "TestSystemInfo.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RTest.h>

void
aFunction()
{
}

RTEST(TestSystemInfo)
{
  RASSERT_MORE(sizeof(char), 0);
  RASSERT_MORE(sizeof(short), 0);
  RASSERT_MORE(sizeof(int), 0);
  RASSERT_MORE(sizeof(long), 0);
  RASSERT_MORE(sizeof(long long), 0);
  RASSERT_MORE(sizeof(void *), 0);
  RASSERT_MORE(sizeof(&aFunction), 0);
  RASSERT_MORE(sizeof(uintptr_t), 0);
  RASSERT_MORE(sizeof(rsize), 0);
  RASSERT_MORE(sizeof(rnumber), 0);
  RASSERT_MORE(sizeof(ruint), 0);
};

void
setup()
{
  Serial.begin(9600);

  while(!Serial)  // for the Arduino Leonardo/Micro only
  {
  }

  RTestApplication testApp;

  testApp.addTest(&RTEST_INSTANCE(TestSystemInfo));
  testApp.run();
}

void
loop()
{
}
