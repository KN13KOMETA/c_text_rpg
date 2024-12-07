#! /bin/bash

rm main
clang main.c -o main --std=c23
./main
