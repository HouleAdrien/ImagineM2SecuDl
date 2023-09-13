#!/bin/bash

rm *.o
rm testsubstitution
rm testinvsubstitution
rm out.pgm
rm test.pgm

g++ -c ImageBase.cpp substitution.cpp
g++ -o testsubstitution ImageBase.o substitution.o


./testsubstitution 01.pgm 128 out.pgm


g++ -c ImageBase.cpp invsubsti.cpp entropie.cpp
g++ -o testinvsubstitution ImageBase.o invsubsti.o entropie.o


./testinvsubstitution out.pgm test.pgm