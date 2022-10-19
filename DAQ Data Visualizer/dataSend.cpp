//Relies on https://github.com/offa/influxdb-cxx
//Relies on c++17

#include "dataSend.h"

std::string URI = std::string("http://") + INFLUX_USER + std::string(":") + INFLUX_PASS + std::string("@") + INFLUX_HOST + std::string(":8086?db=") + INFLUX_BUCKET;

void submitToInflux(double sensordata[]){

    usleep(1000); //For testing. Delete upon recieving access to actual sensor data.

    auto influxdb = influxdb::InfluxDBFactory::Get(URI);
    influxdb->batchOf(1000);
    influxdb->write(influxdb::Point{"Celcius"}.addField("brake_temperature", sensordata[0]));
    influxdb->write(influxdb::Point{"mph"}.addField("car_speed", sensordata[1]));
    influxdb->write(influxdb::Point{"psi"}.addField("oil_pressure", sensordata[2]));
    influxdb->write(influxdb::Point{"Degrees"}.addField("steering_angle", sensordata[3]));
    influxdb->write(influxdb::Point{"Amperes"}.addField("current_draw", sensordata[4]));
    influxdb->write(influxdb::Point{"Millimeters"}.addField("shock_compression", sensordata[5]));
    influxdb->write(influxdb::Point{"Millimeters"}.addField("ride_height", sensordata[6]));
    influxdb->write(influxdb::Point{"mph/s"}.addField("car_acceleration", sensordata[7]));
    influxdb->write(influxdb::Point{"mph"}.addField("airspeed", sensordata[8]));
    influxdb->flushBatch();

    std::cout << "Data Sent" << std::endl; //For testing. Delete upon recieving access to actual sensor data.
}