#include "sensors.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Sensor::CANBox;
bool Sensor::canEnabled = false;
Threads::Mutex Sensor::lock;

Sensor::Sensor(std::vector<uint16_t> canIDs, std::vector<String> valueName, std::vector<String> units, uint8_t pin)
{
    this->canIDs = canIDs;
    this->valueName = valueName;
    this->units = units;
    this->_pin = pin;

    this->data.resize(units.size());

    if (!(Sensor::canEnabled)){
        Sensor::CANBox.begin();
        Sensor::CANBox.setBaudRate(1000000);

        Sensor::canEnabled=true;
    }
}

void Sensor::sendData(uint16_t canID, double data){
    CAN_message_t msg;
    unsigned char *bytes = (unsigned char*)&data;

    msg.id = canID;
    for(unsigned int i = 0; i < sizeof(double); i++) {
        if (i >= 8){
            Serial.println("OS Double is larger than 8 bytes; recompile");
        }

        msg.buf[i] = bytes[i];
    }

    Threads::Scope m(Sensor::lock);
    Sensor::CANBox.write(msg);
}