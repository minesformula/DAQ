#include <Arduino.h>
#include <stdio.h>

#include <FlexCAN_T4.h>
#include "config.h"
#include "sensors.hpp"
#include "sdlogging.h"

void setup() {
  Serial.begin(9600);
  while (!Serial);

  createLog();
}

void loop() {
  
}