//Defining sensor functions

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <arduino.h>
#include "sensors.hpp"

//General Sensor Class
class Sensor {      
    public:
        int value;
        int high;
        int low;
        String type; 
        String unit;

        double getValue(void);
        boolean validate(void);
};

//Analog Sensor: Child class of sensor
class Analog : public Sensor {
    public:
        int pin;
        String equation;
        String sensorName;
};

//I2C Sensor: Child class of sensor
class i2c : public Sensor {
    public:
        int pin1, pin2;
        String hex;
};

//Quadrature Speed Sensor
class QuadSensor{
    public:
        const int chanA = QUAD_CHANNELA;
        const int chanB = QUAD_CHANNELB;

    double detectTime(void);
    double calculateRev(void);
    double calculateLinear(void);
};

#endif
