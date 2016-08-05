#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <StandardCplusplus.h>
#include <RabirdToolkit.h>

#include <RSignal.h>

void Received(int value)
{
  Serial.print("Received ");
  Serial.print(value);
  Serial.println();
}

static RSignal<void (int)> sReceived;
static int sValue = 0;

void setup() {
  Serial.begin(9600);
  sReceived.connect(Received);
}

void loop() {
  delay(3000);
  sReceived.emit(sValue++);
}



