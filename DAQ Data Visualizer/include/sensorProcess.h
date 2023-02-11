#ifndef SENSORPROCESS_H
#define SENSORPROCESS_H

#include <chrono>
using namespace std::chrono;

#include <vector>
#include <cmath>

//GPS class. May be moved onto Logger or Steering Wheel (Different Repo)
//If moved to an Arduino replace chrono class with millis() function
class GPS{
    public:
    GPS(double firstX, double firstY, double secondX, double secondY);
    

    void addPoint(double inX, double inY);

    bool recordLap();

    double getPrevLapTime();
    double getCurrLapTime();
    double getDelta();

    private:
    std::vector<double> _dataX;
    std::vector<double> _dataY;

    double initialX;
    double initialY;
    double direction;

    double slope;
    double YInt;

    auto lapMoment;
    auto prevCheck;
    
    double currLapTime;
    double prevLapTime;
    double delta;

    bool passed;
}

//Sensor class for processing data
class Sensor{
    public:
    Sensor();
    Sensor(const unsigned int canIN, void functionIN (int));

    void processData(int value);

    private:
    unsigned int CANID;
    void (*process) (int); //Function pointer so that a new function only needs to be written for each new sensor
}

#endif