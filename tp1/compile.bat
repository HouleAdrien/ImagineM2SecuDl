@echo off

del *.o
del testsubstitution.exe
del *.exe
del outpermu.pgm
del outsubti.pgm
del test.pgm

g++ -c image_ppm.c
g++ -c permutation.cpp entropie.cpp
g++ -o testpermutation.exe image_ppm.o permutation.o entropie.o

testpermutation.exe 01.pgm 128 outpermu.pgm

@REM g++ -c inv_permutation.cpp entropie.cpp
@REM g++ -o testinvpermutation.exe image_ppm.o inv_permutation.o entropie.o

@REM testinvpermutation.exe outpermu.pgm 128 restored.pgm

g++ -c substitution.cpp
g++ -o testsubstitution.exe image_ppm.o substitution.o

testsubstitution.exe 01.pgm 128 outsubti.pgm

g++ -c invsubsti.cpp entropie.cpp
g++ -o testinvsubstitution.exe image_ppm.o invsubsti.o entropie.o

testinvsubstitution.exe outsubti.pgm test.pgm
testinvsubstitution.exe adrien.pgm test2.pgm
testinvsubstitution.exe secretSubti.pgm test3.pgm