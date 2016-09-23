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
  auto printer = mManager->printer();

  // This pointer will not be free forever
  uint8_t *ptr  = new uint8_t(0xFA);
  uint8_t *ptr2 = new uint8_t(0xEB);

  RRawPointer<uint8_t> rawPtr;
  RRawPointer<uint8_t> rawPtr2(ptr);
  RRawPointer<uint8_t> rawPtr3(rawPtr2);

  RASSERT_TRUE(rawPtr.data() == 0);
  RASSERT_TRUE(rawPtr2.data() == ptr);
  RASSERT_TRUE(rawPtr3.data() == ptr);
  RASSERT_TRUE(rawPtr3.data() == rawPtr2.data());
  RASSERT_TRUE(rawPtr == 0);
  RASSERT_TRUE(rawPtr2 == ptr);
  RASSERT_TRUE(rawPtr3 == ptr);
  RASSERT_TRUE(rawPtr3 == rawPtr2.data());
  RASSERT_EQUAL(rawPtr3, rawPtr2);

  rawPtr.reset(ptr2);

  RASSERT_TRUE(rawPtr.data() == ptr2);
  RASSERT_EQUAL(*rawPtr, 0xEB);
  RASSERT_EQUAL(*rawPtr3, 0xFA);

  rawPtr = rawPtr3;

  RASSERT_TRUE(rawPtr.data() == ptr);
  RASSERT_TRUE(rawPtr.data() == rawPtr2.data());

  rawPtr.reset();
  rawPtr3.reset();

  RASSERT_TRUE(rawPtr.data() == NULL);
  RASSERT_TRUE(rawPtr3.data() == NULL);
  RASSERT_TRUE(rawPtr == NULL);
  RASSERT_TRUE(rawPtr3 == NULL);
  RASSERT_TRUE(rawPtr2 == ptr);
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
