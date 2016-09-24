# 2 "TestSystemInfo.ino"

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RTest.h>
#include <RRawPointer.h>
#include <RSharedPointer.h>

RTEST(TestSystemInfo)
{
  auto printer   = mManager->printer();
  auto formatter = RFormatter(printer);

  formatter("Size of int : %s").arg(sizeof(int));
  formatter("Size of uintptr_t : %s").arg(sizeof(uintptr_t));
  formatter("Size of rsize : %s").arg(sizeof(rsize));
  formatter("Size of rnumber : %s").arg(sizeof(rnumber));
  formatter("Size of ruint : %s").arg(sizeof(ruint));
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
