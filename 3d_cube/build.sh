#!/bin/sh

set -xe 

clang -Wall -o 3d_cube 3d_cube.c -lSDL2 -lm 

./3d_cube
