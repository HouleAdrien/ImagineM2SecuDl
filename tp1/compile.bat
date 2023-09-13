@echo off

del *.o
del testsubstitution.exe
del *.exe
del *.o
del outpermu.pgm
del outsubti.pgm
del test.pgm

g++ -c ImageBase.cpp permutation.cpp entropie.cpp
g++ -o testpermutation.exe ImageBase.o permutation.o entropie.o

testpermutation.exe 01.pgm 128 outpermu.pgm

g++ -c ImageBase.cpp inv_permutation.cpp entropie.cpp
g++ -o testinvpermutation.exe ImageBase.o inv_permutation.o entropie.o

testinvpermutation.exe outpermu.pgm 128 restored.pgm

g++ -c ImageBase.cpp substitution.cpp
g++ -o testsubstitution.exe ImageBase.o substitution.o

testsubstitution.exe 01.pgm 128 outsubti.pgm

g++ -c ImageBase.cpp invsubsti.cpp entropie.cpp
g++ -o testinvsubstitution.exe ImageBase.o invsubsti.o entropie.o

testinvsubstitution.exe outsubti.pgm test.pgm
