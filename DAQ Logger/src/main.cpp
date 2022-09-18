#include <Arduino.h>
#include "config.h"
#include "sensors.h"
#include "IRTherm/irtherm.h"

void setup() {
  Serial.begin(9600);
}

//This version is testing connection with quadrature sensor
void loop() {
  QuadSensor vsense;
  
  for (int i = 0; i < 10; i++){
    Serial.println("Time: ");
    Serial.println(vsense.detectRev());
  }
}