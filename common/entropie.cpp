#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <stdlib.h>



int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, nTaille;
    
    if (argc != 2){
        printf("Usage: ImageIn.pgm\n"); 
        exit (1) ;
    }
    
    sscanf (argv[1],"%s",cNomImgLue) ;

    OCTET *ImgIn;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    int histo[256];
    double pourcentage = 0.98 * nTaille;

    for (int i = 0; i < 256; i++){
        histo[i] = 0;
    }

    for(int i = 0; i < nTaille; i++){
        histo[ImgIn[i]]++;
    }

    double entropie = 0;
    double temp;
    double pi;
    for(int i = 0; i < 256; i++){
        if(histo[i] == 0){
            temp = 0;
        }
        else{
            pi = double(histo[i])/nTaille;
            temp = pi * log2(pi);
            entropie -= temp;
        }
    }

    std::cout<<"L'entropie de l'image est de : "<<entropie<<std::endl;
    free(ImgIn); 
    return 1;
}
