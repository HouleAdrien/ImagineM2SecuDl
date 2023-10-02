@echo off

g++ -c ..\common\image_ppm.c
g++ -c main.cpp
g++ -o app image_ppm.o main.o

app 05.pgm 05lsbmessage.pgm 05msbmessage.pgm message.txt