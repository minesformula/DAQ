#include "ShipFile.h"

void shipData(std::ifstream& fileIn){
    std::vector<std::string> measurements, units;
    std::string currString;

    fileIn >> currString;
    fileIn >> currString;
    while (currString != "0.000"){

        if (currString.at(0) == '(' || currString.at(0) == '['){
            units.push_back(currString);
            fileIn >> currString;
        }
        else {
            measurements.push_back(currString);

            fileIn >> currString;
            if (currString.at(0) != '(' && currString.at(0) != '['){
                measurements[measurements.size() - 1] = currString;
                fileIn >> currString;
            }
        }
    }

    std::cout << "Working - Please Wait" << std::endl;

    std::vector<double> values;
    values.push_back(0.000);

    while (currString != "Lap:"){
        while (measurements.size() > values.size()){
            fileIn >> currString;
            if (currString == "Lap:"){
                std::cout << "Done" << std::endl;
                return;
            }
            else {
                values.push_back(stod(currString));
            }
        }

       submitToInflux(measurements, units, values);
    }
}

void submitToInflux(const std::vector<std::string> measurements, const std::vector<std::string> units, std::vector<double>& values){
    std::string URI = std::string("http://") + FILE_INFLUX_USER + std::string(":") + FILE_INFLUX_PASS + std::string("@") + FILE_INFLUX_HOST + std::string(":8086?db=") + FILE_INFLUX_BUCKET;

    auto influxdb = influxdb::InfluxDBFactory::Get(URI);
    influxdb->batchOf(1000000);
    for (int i = 0; i < measurements.size(); i++){
        influxdb->write(influxdb::Point{units[i]}.addField(measurements[i], values[i]));
    }
    influxdb->flushBatch();

    values.clear();

    return;
}
