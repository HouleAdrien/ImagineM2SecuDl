#!/bin/bash


g++ -c ../common/image_ppm.c 

g++ -c main.cpp  aes.cpp
g++ -o testAes image_ppm.o main.o aes.o

./testAes baboon.pgm outnoiseECBBaboon.pgm outdecryptnoiseECBBaboon.pgm
./testAes radio.pgm outnoiseECBRadio.pgm  outdecryptnoiseECBRadio.pgm