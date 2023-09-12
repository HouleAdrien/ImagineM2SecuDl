@echo off

del *.o
del testsubstitution.exe
del testinvsubstitution.exe
del out.pgm
del test.pgm

g++ -c ImageBase.cpp substitution.cpp
g++ -o testsubstitution.exe ImageBase.o substitution.o

testsubstitution.exe 01.pgm 128 out.pgm

g++ -c ImageBase.cpp invsubsti.cpp
g++ -o testinvsubstitution.exe ImageBase.o invsubsti.o

testinvsubstitution.exe out.pgm 128 test.pgm
