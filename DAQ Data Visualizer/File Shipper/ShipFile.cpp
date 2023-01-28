#include <chrono>
using namespace std::chrono;

#include "ShipFile.h"

void shipData(std::ifstream& fileIn){
    std::vector<std::string> measurements, units;
    std::string currString;

    auto start = high_resolution_clock::now();

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

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
    //std::cout << "First Line Complete: " << duration.count()  << " μs" << std::endl;

    std::vector<double> values;
    values.push_back(0.000);

    while (currString != "Lap:"){
        fileIn >> currString;
        if (currString == "Lap:"){
            duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
            std::cout << "Full File Read: " << duration.count()  << " μs" << std::endl;
            break;
        }
        else {
            values.push_back(stod(currString));
        }
    }

    submitToInflux(measurements, units, values);
    std::cout << "Done" << std::endl;
}

void submitToInflux(const std::vector<std::string> measurements, const std::vector<std::string> units, std::vector<double>& values){
    //std::string URI = std::string("http://") + FILE_INFLUX_USER + std::string(":") + FILE_INFLUX_PASS + std::string("@") + FILE_INFLUX_HOST + std::string(":8086?db=") + FILE_INFLUX_BUCKET;
    std::string URI = std::string("http://member:passcode@localhost:8086?db=daqactual");
    auto start = high_resolution_clock::now();

    auto influxdb = influxdb::InfluxDBFactory::Get(URI);
    influxdb->batchOf(values.size());

    const int readValues = values.size()/measurements.size();
    int j = 0;

    while (j < values.size()){
        for (int i = 0; i < measurements.size(); i++){
            influxdb->write(influxdb::Point{units[i]}.addField(measurements[i], values[j]));
            j++;
        }
    }

    influxdb->flushBatch();

    values.clear();

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    std::cout << "Submission Time: " << duration.count() << " μs" << std::endl;
    return;
}
