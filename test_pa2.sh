#!/bin/sh
# Author: Amittai Aviram - aviram@bc.edu

PROG=lextest
INPUT=merge.tig
OUTPUT=output.txt
EXPECTED=expected_pa2.txt

echo Building $PROG ...
make clean && make
if [ $? != 0 ]
then
    echo "\n ***** BUILD FAILURE ***** \n"
    exit 1
fi

echo Building complete.

echo Running ...
./${PROG} ${INPUT} > ${OUTPUT}
echo Running complete.

echo Comparing real and expected output.
DIFF=$(diff --strip-trailing-cr ${OUTPUT} ${EXPECTED})
if [ "$DIFF" != "" ]
then
    printf "\nXXXXXXXX UNEXPECTED OUTPUT: XXXXXXXX\n\n"
    printf "In each pair below, your output appears above the expected output.\n"
    printf "$DIFF\n\n"
else
    printf "\n======== CORRECT ========\n\n"
fi
rm output.txt

