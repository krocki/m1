#!/bin/bash

set -x

INCLUDE=/opt/OpenBLAS/include/
LIB=/opt/OpenBLAS/lib/
LINKFLAGS=-lopenblas
OUT=vec

gcc -c -O2 mat.c -o mat.o
gcc -c -O2 vec.c -o vec.o -I${INCLUDE} -Wfatal-errors
gcc -O2 -L${LIB} mat.o vec.o ${LINKFLAGS} -o ${OUT}
