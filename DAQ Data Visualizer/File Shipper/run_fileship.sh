#!/bin/bash
  
if [ -z "$1" ]
 then	
  echo "Usage: ./run_fileship <fileLocation>"
  exit

 else
  echo "Shipping data from $1"
  influx delete -b daqactual --start 2010-01-02T23:00:00Z --stop 2100-01-02T23:00:00Z
  ./fileShipper $1
fi
