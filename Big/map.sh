#!/usr/bin/env bash

if (($# < 2))
then
    exit 1
fi

if ! [ -f $1 ]
then
    exit 1
fi

FILE=$1
readonly REGEXP='^[0-9]+$'
shift

for routeId in $@
do
    if ! [[ $routeId =~ $REGEXP ]] || ((1 > $routeId || $routeId > 999))
    then
	exit 1
    fi
done

for routeId in $@
do
    grep "^$routeId;" $FILE | 
    awk -v id=$routeId -F';' 'BEGIN{sum=0}
	{for(i=3;i<=NF;i+=3) sum+=$i}
	END{if (sum != 0) print id ";" sum}'   
done
