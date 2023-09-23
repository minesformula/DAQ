#include "Sensors/Potentiometer.h"


std::vector<Potentiometer> Potentiometer::sensorList;

void Potentiometer::startQuery(){
    threads.addThread(Potentiometer::queryList);
}

void Potentiometer::queryList(){
    while(true){
    for (unsigned int i = 0; i < Potentiometer::sensorList.size(); i++){
        sensorList[i].query();
        Serial.print("query ");
        Serial.print(i);
        Serial.print(" ");
    }

    Serial.print("query");

    threads.delay(5000);
    }
}

void Potentiometer::query(){
    data[0] = (double)analogRead(_pin);
    Serial.println(data[0]);
    sendData(canIDs[0], data[0]);
}