#!/bin/sh


set -xe

clang -Wall -Wextra -o example example.c


./example
