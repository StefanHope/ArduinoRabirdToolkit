# 2 "TestSystemInfo.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RTest.h>

RTEST(TestSystemInfo)
{
  RASSERT_MORE(sizeof(int), 0);
  RASSERT_MORE(sizeof(uintptr_t), 0);
  RASSERT_MORE(sizeof(rsize), 0);
  RASSERT_MORE(sizeof(rnumber), 0);
  RASSERT_MORE(sizeof(ruint), 0);
  RASSERT_MORE(sizeof(void *), 0);
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
