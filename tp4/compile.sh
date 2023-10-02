#!/bin/bash


g++ -c ../common/image_ppm.c 

g++ -c main.cpp  
g++ -o app image_ppm.o main.o 

./app test.ppm