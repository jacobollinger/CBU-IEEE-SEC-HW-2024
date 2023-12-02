#! /bin/bash

rm -f ./annotations.csv

for i in $(find ./images/raw -type f); do
    file=${i##*/}
    path=${i%/*}
    type=${path##*/}

    if [ "$type" == "small_package" ]; then
        number=1
    elif [ "$type" == "thruster" ]; then
        number=2
    elif [ "$type" == "large_package" ]; then
        number=3
    elif [ "$type" == "fuel_tank_thruster_assembly" ]; then
        number=4
    elif [ "$type" == "fuel_tank" ]; then
        number=5
    else
        number=0
    fi

    echo "$file => $type ($number))"
    echo "$file,$type,$number" >> ./annotations.csv
done
