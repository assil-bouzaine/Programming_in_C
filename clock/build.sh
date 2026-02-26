#!/bin/sh


set -xe
clang -Werror -Wall -o clock clock.c -lraylib -lm

./clock
