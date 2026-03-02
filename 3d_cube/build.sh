#!/bin/sh

set -xe 

clang -Wall -o 3d_cube 3d_cube.c `sdl2-config --cflags --libs`

./3d_cube
