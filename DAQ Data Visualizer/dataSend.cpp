//Relies on https://github.com/offa/influxdb-cxx
//Relies on c++17

#include "dataSend.h"
#include <InfluxDB.h>
#include <InfluxDBFactory.h>

time_t start = time(0);

void submitToInflux(float braketemp){
    double elapTime = difftime(time(0), start);

    // Provide complete URI
    auto influxdb = influxdb::InfluxDBFactory::Get("http://localhost:8086?db=daqtesting");
    influxdb->write(influxdb::Point{"test"}.addField("brake temperature", braketemp).addTag("host", "localhost"));
}