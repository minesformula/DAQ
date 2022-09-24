#include <Arduino.h>
#include <stdio.h>

#include "config.h"
#include "sensors.h"
#include "sdlogging.h"
#include "IRTherm/irtherm.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  createLog();
}

//This version is testing connection with quadrature sensor
void loop() {
  QuadSensor vsense;
  double revtime, runtime;
  char logWrite [50];
  
  for (int i = 0; i < 10; i++){
    revtime = vsense.calculateRev();
    Serial.println("Revolutions per Second: ");
    Serial.println(revtime);

    runtime = millis();
    sprintf(logWrite, "%d Revolutions per Second: %f\0", runtime, revtime);
    writeToLog(logWrite);
  }
}