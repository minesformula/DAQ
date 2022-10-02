//Defining sensor functions

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <arduino.h>
#include "sensors.hpp"

//General Sensor Class
class Sensor {      
    public:
        boolean validate(const double);
        String getType(void);
        String getUnit(void);

    protected:
        int highVal;
        int lowVal;
        const String sensorType = "undefined"; 
        String unit;
};

//Analog Sensor: Child class of sensor
class Analog : public Sensor {
    public:
        double getAnalog(void);
        int getDigital(void);
        double calculateLinear(const double);
        double calculateLinear(const double, const double);

    private:
        int pin;
        int constant;
        const String sensorType = "Analog";
};

//I2C Sensor: Child class of sensor
class I2C : public Sensor {
    public:
        String getHexAddress(void);
    private:
        int pin1;
        int pin2;
        String hexAddress;
        const String sensorType = "I2C";

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
