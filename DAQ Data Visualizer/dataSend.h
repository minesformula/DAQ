#include <time.h>

#ifndef INFLUXDB_H
#define INFLUXDB_H

// Function to submit metrics to Influx
void submitToInflux(float braketemp);
#endif