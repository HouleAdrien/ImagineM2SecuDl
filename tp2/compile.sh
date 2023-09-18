#!/bin/bash


g++ -c ../common/image_ppm.c 

g++ -c main.cpp 
g++ -o testAes image_ppm.o main.o 


./testAes baboon.pgm test.pgm