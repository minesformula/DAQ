#include <Arduino.h>
#include <stdio.h>

#include "config.h"
#include "sensors.hpp"
#include "sdlogging.h"
#include "irtherm.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  createLog();
}

//This version is testing connection with quadrature sensor
void loop() {
  QuadSensor vsense;
  double revtime;
  char logWrite [50];
  
  for (int i = 0; i < 10; i++){
    revtime = vsense.calculateRev();
    Serial.println("Revolutions per Second: ");
    Serial.println(revtime);

    sprintf(logWrite, "%d Revolutions per Second: %f", millis(), revtime);
    writeToLog(logWrite);
  }
}