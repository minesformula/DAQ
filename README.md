# DAQ-Vehicle
 Code for the physical DAQ(Hermes) on the vehicle


## Visualizer QuickStart (Influx-CXX, Grafana and InfluxDB)

This project makes use of InfluxDB and Grafana to record and visualize data respectively. The visualizer must be installed on a Raspberry Pi 4+ and a 64 bit operating systems in order to comply with InfluxDB requirements. 

The below installation steps assume you are using Ubuntu on a Raspberry PI that fits the above requirements.

### Influx-CXX Installation

Run `sudo apt install cmake g++ make git curl` on your Raspberry PI command line. This command, on success, will install the tools necessary to install Influx-CXX and it's dependencies.

Run the below command. This will install all git repos necessary build them and then remove the leftovers from the system.

```
git clone https://github.com/catchorg/Catch2
cd Catch2
mkdir build && cd build
cmake ..
sudo make install
cd ../..

git clone https://github.com/rollbear/trompeloeil
cd trompeloeil
mkdir build && cd build
cmake ..
sudo make install
cd ../..

git clone https://github.com/offa/influxdb-cxx
cd influxdb-cxx
mkdir build && cd build
cmake ..
sudo make install
cd ../..

sudo rm -r Catch2
sudo rm -r trompeloeil
sudo rm -r influxdb-cxx
```

Once the process has completed influxdb-cxx will be installed on the system. There may still be missing repositories required for the visualizer to compile.

### InfluxDB Installation

Run the below command in your Raspberry Pi command line to install the Influx CLI. This is necessary for initial setup and proper authentication control later in the process.
```
wget https://dl.influxdata.com/influxdb/releases/influxdb2-client-2.4.0-linux-amd64.tar.gz
tar xvzf path/to/influxdb2-client-2.4.0-linux-amd64.tar.gz
sudo cp influxdb2-client-2.4.0-linux-amd64/influx /usr/local/bin/
```

Once Influx CLI is installed run `influx setup` and follow the prompts to complete database setup.

After answering each prompt run `influx bucket ls` and copy the ID of the bucket that was just created via influx setup. Using your copied BUCKET_ID Run the below command replacing BUCKET_ID, USERNAME, PASSWORD and ORG_NAME with their corresponding values.
```
influx v1 auth create --write-bucket <BUCKET_ID>  --username <USERNAME> --password <PASSWORD> --org <ORG_NAME>
```

This auth account will be used with influxdb-cxx to authorize the writing of information to the influx database (a database and a bucket are functionally the same in this case). Find the "influxDB_Config.h" file  in the "DAQ Data Visualizer" directory and replace each of the following constants with their corresponding value. 
```
#define INFLUX_HOST "<IP_ADDRESS>" //Host IP Address goes here
#define INFLUX_BUCKET "<BUCKET_NAME>" //The name of the influx bucket/databse goes here
#define INFLUX_USER "<USERNAME>" //Username of your auth account goes here
#define INFLUX_PASS "<PASSWORD>" //Password of your auth account goes here
```
There must be no spaces in these values though if you created a value with a space it can be accounted for like "This%20is%20an%20example" remember if you can't put the url into your search bar it will not work in the program.

Once this is complete type `influxd` into your command line. This should begin the influxDB service.

InfluxDB should be capable of receiving data from the submitToInflux function if it is not receiving data or the program is throwing an error (especially a 400 or 401 error) recheck the previous steps.

### Grafana Installation

To be written...
