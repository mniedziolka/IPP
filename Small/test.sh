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
	./${prog} < ${file} 1>${file%in}myout 2>${file%in}myerr
	if diff ${file%in}out ${file%in}myout &>/dev/null
	then
		echo -e "${GREEN}[Standard]	${COLOR_OFF}${file}"
	else
		echo -e "${RED}[Standard]	${COLOR_OFF}${file}"
	fi

	if diff ${file%in}err ${file%in}myerr &>/dev/null
	then 
		echo -e "${GREEN}[Diagnostic]	${COLOR_OFF}${file}"
	else
		echo -e "${RED}[Diagnostic]	${COLOR_OFF}${file}"
	fi

	valgrind --error-exitcode=15 --main-stacksize=40000000 --leak-check=full ./${prog} < ${file} &>/dev/null
	if [ $? -ne 15 ]
	then
		echo -e "${GREEN}[Memory]	${COLOR_OFF}${file}"
	else
		echo -e "${RED}[Memory]	${COLOR_OFF}${file}"
	fi
done
