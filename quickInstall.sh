#!/bin/bash

cd ~

git clone https://github.com/catchorg/Catch2
git clone https://github.com/rollbear/trompeloeil
git clone https://github.com/offa/influxdb-cxx

sudo apt-get install g++
sudo apt-get install cmake
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libboost1.71-all-dev

cd Catch2
mkdir build && cd build
cmake ..
sudo make install
cd ../..

cd trompeloeil
mkdir build && cd build
cmake ..
sudo make install
cd ../..

cd influxdb-cxx
mkdir build && cd build
cmake ..
sudo make install
cd ../..

sudo rm -r Catch2
sudo rm -r trompeloeil
sudo rm -r influxdb-cxx

sudo apt-get install influxdb
sudo systemctl unmask influxdb
sudo systemctl start influxdb
sudo systemctl enable influxdb

