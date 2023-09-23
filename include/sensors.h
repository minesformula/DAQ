// Defining sensor functions

#ifndef SENSORS_H
#define SENSORS_H

#include <arduino.h>
#include <FlexCAN_T4.h>
#include <TeensyThreads.h>
#include <vector>

// General Sensor Class
class Sensor
{
public:
    Sensor(std::vector<uint16_t> canID, std::vector<String> valueName, std::vector<String> units, uint8_t pin);

    std::vector<String> getType(){ return valueName;};
    std::vector<String> getUnit(){ return units;};

    int getPin() {return _pin;};
    void setPin(uint8_t newPin) {
        Threads::Scope m(Sensor::lock);
        _pin = newPin;
    };

    void startQuery();


protected:
    virtual void query() = 0;

    void sendData(uint16_t canID, double data);

    std::vector<uint16_t> canIDs;
    static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CANBox;
    static bool canEnabled;


    static Threads::Mutex lock;
    std::thread* queryThread;

    std::vector<String> units;
    std::vector<String> valueName;
    std::vector<double> data;

    uint8_t _pin;
};

#endif
