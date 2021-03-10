#!/bin/bash

set -x

OUT=vec_acc
gcc -Ofast mat.c vec.c -framework Accelerate -o vec_acc
