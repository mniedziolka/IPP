#!/bin/bash

if [ ! $# -eq 2 ]; then 
	echo "Usage ./test.sh prog dir"
	exit 1
fi

prog=$1
dir=$2

if [ ! -f quantization ]; then
	echo "Run make first!"
	exit 2
fi

for file in ${dir}/*.in
do
	./quantization < ${f} > ${f%in}out
done
