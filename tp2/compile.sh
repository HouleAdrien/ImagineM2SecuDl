#!/bin/bash


g++ -c ../common/image_ppm.c 

g++ -c main.cpp  aes.cpp
g++ -o testAes image_ppm.o main.o aes.o

./testAes baboon.pgm outCFBBaboon128.pgm
./testAes radio.pgm outCFBRadio128.pgm