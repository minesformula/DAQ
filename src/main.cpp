#include <Arduino.h>
#include <stdio.h>
#include <vector>

#include <FlexCAN_T4.h>
#include "config.h"
#include "sensors.h"
#include "Sensors/Potentiometer.h"

std::vector<Sensor*> *sensorList;

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Initialized");
  sensorList = new std::vector<Sensor*>;

  sensorList->push_back(new Potentiometer(26));
  Potentiometer::startQuery();
}

void loop()
{
}