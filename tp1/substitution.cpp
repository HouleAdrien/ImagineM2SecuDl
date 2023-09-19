#include "image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "entropie.h"


int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int key;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm 8_bits_key ImageOut.pgm \n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%s", cNomImgEcrite);

    OCTET *ImgIn;
    OCTET *ImgOut;

    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);

    srand(key);


    for (int i = 0; i < nTaille; ++i)
    {
        if (i == 0)
        {
            ImgIn[i] = ((rand() % 256) + ImgIn[i]) % 256;
        }
        else
        {
            ImgIn[i] = ((ImgIn[i - 1] + ImgIn[i]) + (rand() % 256)) % 256;
        }
    }

        for (int i = 0; i < nTaille; ++i)
        {
            ImgOut[i] = ImgIn[i];
        }
    
    Entropie entropie;

	double entropy =  entropie.GetEntropieOfImage(ImgOut,nTaille);

    std::cout << "entropie après subtitution : " << entropy << std::endl;

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
