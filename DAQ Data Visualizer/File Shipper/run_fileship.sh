#!/bin/bash
  
if [ -z "$1" ]
 then	
  echo "Usage: ./run_fileship <fileLocation> <OptionalCSVSaveName>"
  exit

 else
  echo "Shipping data from $1"
  influx delete -b daqactual --start 2010-01-02T23:00:00Z --stop 2100-01-02T23:00:00Z
  ./fileShipper $1

  if [ -z "$2" ]
  then
   echo "No Filename Specified for Raw CSV Data File"
  else
   influx query 'from(bucket:"daqactual")|>range(start:-7d)' --raw > ./csv_raw/"$2"
   echo "Wrote InfluxDB Raw CSV File to ./csv_raw/{$2}"
  fi
fi
