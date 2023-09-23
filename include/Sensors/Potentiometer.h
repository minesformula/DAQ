#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "sensors.h"

class Potentiometer : public Sensor {
    public:
        Potentiometer(uint8_t pin) : Sensor(std::vector<uint16_t>{22}, std::vector<String>{"aThing"}, std::vector<String>{"aUnit"}, pin){
            sensorList.push_back(*this);
        };
        static void startQuery();

    private:
        void query();

        static void queryList();
        static std::vector<Potentiometer> sensorList;
};

#endif