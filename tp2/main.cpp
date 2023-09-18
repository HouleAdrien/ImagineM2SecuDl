#include "../common/image_ppm.h"
#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int key;

    if (argc != 3)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn;
    OCTET *ImgOut;

    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);






    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
