#!/bin/sh

set -xe
clang -Werror -Wall -o fractal_tree fractal_tree.c -lraylib -lm

./fractal_tree
