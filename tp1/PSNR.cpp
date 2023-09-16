#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

#define VALMAX 255

int main(int argc, char* argv[]){
    char cNomImgLue1[250], cNomImgLue2[250];
    int nH, nW, nTaille;
    
    if (argc != 3) {
        printf("Usage: ImageIn1.ppm ImageIn2.ppm\n"); 
        exit (1) ;
    }
    
    sscanf (argv[1],"%s",cNomImgLue1) ;
    sscanf (argv[2],"%s",cNomImgLue2);

    OCTET *ImgIn1, *ImgIn2;
   
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn1, OCTET, nTaille);
    lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);

    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

    double eqm = 0;

    for(int i = 0; i < nTaille; i++){
        eqm += pow((ImgIn1[i] - ImgIn2[i]), 2);
    }

    eqm /= nTaille;

    std::cout<<"eqm : "<< eqm<<std::endl;

    double PSNR = 10 * log10((VALMAX*VALMAX)/eqm);

    std::cout<<"PSNR : "<<PSNR<<std::endl;

    return 0;
}