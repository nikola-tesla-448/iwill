#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./cliwill.sh
# Run single cmd:  sudo ./cliwill.sh <cliwill paramers>

PREFIX="docker-compose exec nodiwilld cliwill"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "cliwill " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX "$@"
fi
