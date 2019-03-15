#!/bin/bash

if [ ! $# -eq 2 ]; then 
	echo "Usage ./test.sh prog dir"
	exit 1
fi

prog=$1
dir=$2

if [ ! -x ${prog} ]; then
	echo "Run make first!"
	exit 2
fi

for file in ${dir}/*.in
do
	./${prog} < ${file} 1>${file%in}myout 2>${file%in}myerr
	diff ${file%in}out ${file%in}myout 1>/dev/null 2>&1 || break
	diff ${file%in}err ${file%in}myerr 1>/dev/null 2>&1 || break
done
