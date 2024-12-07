#! /bin/bash

rm main
clang main.c -o main --std=c99
./main
