#!/bin/bash

if [ -z "$1" ]
 then
  echo "Usage: ./fileDownload.sh <SaveFileName.csv>"
 else
  curl -XPOST http://104.131.85.212:8086/api/v2/query -sS \
  -H 'Accept:application/csv' \
  -H 'Content-type:application/vnd.flux' \
  -d 'from(bucket:"daqactual")
        |> range(start:-7d)' > ./csv_raw/"$1"
fi