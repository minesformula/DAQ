#include <string>
#include <Arduino.h>
#include "config.h"
#include "sensors.hpp"

//Sensor Class Functions
//Returns true if the passed value is between high and low
boolean Sensor::validate(const double value){
  if (value >= lowVal && value <= highVal){
    return true;
  }

  return false;
};

//Returns the type of Sensor as a String(I2C, Analog or Undefined)
String Sensor::getType(){
  return sensorType;
};

//Returns the unit name as a String
String Sensor::getUnit(){
  return unit;
};



//Analog Class Functions
//reads analog value: If the value returns false via validate returns -1
double Analog::getAnalog(){
  double value = analogRead(pin);

  if(validate(value)) {
    return value;
  }
  return -1;
};

//Converts analog input into digital by measuring if it is above the range midpoint. Returns 1 for high and 0 for low
int Analog::getDigital(){
  const double threshold = (highVal-lowVal)/2 + lowVal;
  const double value = getAnalog();
  if (value >= threshold){
    return 1;
  };

  return 0;
};

//ses analog value and a multiplicative constant to make a linear calculation
double Analog::calculateLinear(const double a){
  return a * getAnalog();
};

//Like the other function but with a value to add as well
double Analog::calculateLinear(const double a, const double b){
  return a * getAnalog() + b;
};



//I2C Class Functions
//Returns hex address of I2C sensor as a String
String I2C::getHexAddress(){
  return hexAddress;
};






//QuadSensor Class Function
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


