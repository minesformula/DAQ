#include "influxDB_Config.h"
#include <time.h>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <InfluxDBFactory.h> 
#include <InfluxDB.h>
#include <unistd.h>

#ifndef INFLUXDB_H
#define INFLUXDB_H

// Function to submit metrics to Influx
void submitToInflux(double sensordata[]);
#endif