#include <Arduino.h>
#include <stdio.h>
#include <vector>

#include <FlexCAN_T4.h>
#include "config.h"
#include "sensors.hpp"

std::vector<Sensor> *sensorList;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }
}

void loop()
{
}