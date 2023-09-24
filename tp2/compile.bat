g++ -c ../common/image_ppm.c 

g++ -c main.cpp  aes.cpp
g++ -o testAes.exe image_ppm.o main.o aes.o

testAes.exe baboon.pgm outnoiseCTRBaboon.pgm outdecryptnoiseCTRBaboon.pgm
testAes.exe radio.pgm outnoiseCTRRadio.pgm  outdecryptnoiseCTRRadio.pgm