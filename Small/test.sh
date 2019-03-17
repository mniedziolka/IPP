#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
COLOR_OFF='\033[0m'

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
	valgrind --leak-check=full ./${prog} < ${file}
	./${prog} < ${file} 1>${file%in}myout 2>${file%in}myerr
	if diff ${file%in}out ${file%in}myout 1>/dev/null 2>&1
	then 
		echo -e "${GREEN}[Standard]	${COLOR_OFF}${file}"
	else
		echo -e "${RED}[Standard]	${COLOR_OFF}${file}"
	fi
	if diff ${file%in}err ${file%in}myerr 1>/dev/null 2>&1
	then 
		echo -e "${GREEN}[Diagnostic]	${COLOR_OFF}${file}"
	else
		echo -e "${RED}[Diagnostic]	${COLOR_OFF}${file}"
	fi
done
