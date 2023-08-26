// Defining sensor functions

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <arduino.h>
#include <FlexCAN_T4.h>
#include <TeensyThreads.h>
#include <vector>
#include "sensors.hpp"

// General Sensor Class
class Sensor
{
public:
    Sensor(int canID, String valueName, String units, void (*query)(Sensor *));

    String getType();
    String getUnit();

private:
    uint16_t canID;
    FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CANBox;

    String units;
    String valueName;
    std::vector<int> data;

    void (*sensorFunc)(Sensor *thisSensor);

    std::thread *sensorThread;
};

Sensor::Sensor(int canID, String valueName, String units, void (*query)(Sensor *))
{
    this->canID = canID;
    this->valueName = valueName;
    this->units = units;

    sensorFunc = query;

    sensorThread = new std::thread(sensorFunc, this);
}

#endif
