#include <string>
#include <Arduino.h>
#include "config.h"
#include "sensors.hpp"

//Returns time it takes for one gap/tooth to pass
double QuadSensor::detectTime(void) {
  const int startval = ((analogRead(chanA)/1024)+0.5);
  int readval = startval;

  double time = 0;

  while (readval == startval){
    delay(10);
  }

  while (readval != startval && time < 1000){
    delay(10);
    time += 0.01;

    readval = ((analogRead(chanA)/1024)+0.5);
  }

  return time;
};

//Calculates revolutions per second and returns it. TONE_NUM is number of gaps+teeth on tone wheel.
double QuadSensor::calculateRev() {
  return 1/(TONE_NUM * detectTime());
}

double QuadSensor::calculateLinear() {
  //output in mm/sec
  return 0.08/(detectTime());
}


