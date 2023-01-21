#!/bin/bash

while getopts 'f:' OPTION; do
  case "$OPTION" in
    f)
     fvalue="$OPTARG"
      echo "Shipping data from $OPTARG"
      influx delete -b daqactual --start 2010-01-02T23:00:00Z --stop 2100-01-02T23:00:00Z
      ./fileship $OPTARG
      ;;
    ?)
      echo "script usage: $(basename \$0) [-f somefilepath]" >&2
      exit 1
      ;;
  esac
done