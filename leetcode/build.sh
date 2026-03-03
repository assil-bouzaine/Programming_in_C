#!/bin/sh
#build.sh



set -xe
clang -Wall -Werror -o main main.c leetcode.c



./main
