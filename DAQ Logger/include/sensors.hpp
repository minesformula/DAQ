//Defining sensor functions

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <arduino.h>
#include "sensors.hpp"

//General Sensor Class
class Sensor {      
    public:
        double getValue(void);
        boolean validate(void);

    protected:
        int value;
        int high;
        int low;
        String type; 
        String unit;
};

//Analog Sensor: Child class of sensor
class Analog : public Sensor {
    public:
        double calculate(double a, double b);

    private:
        int pin;
        int constant;
};

//I2C Sensor: Child class of sensor
class i2c : public Sensor {
    public:
        String getHex(void);
    private:
        int pin1;
        int pin2;
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
