@echo off

del *.o
del testsubstitution.exe
del *.exe
del outpermu.pgm
del outsubti.pgm
del test.pgm

g++ -c image_ppm.c entropie.cpp PSNR.cpp histo.cpp 

g++ -c permutation.cpp 
g++ -o testpermutation.exe image_ppm.o permutation.o entropie.o

testpermutation.exe baboon.pgm 128 outpermu.pgm
testpermutation.exe lena.pgm 29 outpermulena.pgm
testpermutation.exe 01.pgm 210 outpermu01.pgm


g++ -o PSNR.exe image_ppm.o PSNR.o

PSNR.exe baboon.pgm outpermu.pgm

g++ -c inv_permutation.cpp
g++ -o testinvpermutation.exe image_ppm.o inv_permutation.o entropie.o

testinvpermutation.exe outpermu.pgm 128 restoredpermu.pgm

g++ -c substitution.cpp
g++ -o testsubstitution.exe image_ppm.o substitution.o

testsubstitution.exe baboon.pgm 128 outsubti.pgm


testsubstitution.exe baboon.pgm 29 outsubstilena.pgm
testsubstitution.exe baboon.pgm 210 outsubsti01.pgm

PSNR.exe baboon.pgm outsubti.pgm

g++ -c invsubsti.cpp 
g++ -o testinvsubstitution.exe image_ppm.o invsubsti.o entropie.o

testinvsubstitution.exe outsubti.pgm restoredsubti.pgm

g++ -c histo.cpp 
g++ -o testhisto.exe image_ppm.o histo.o
