#include "../common/image_ppm.h"
#include "aes.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250];

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
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F}; 
    unsigned char iv[256];

    for(int i=0; i < 256; i++){
        iv[i] = 0x00;
    }

    const AESKeyLength keyLength = AESKeyLength::AES_128;

    AES aesInstance(keyLength);

    //unsigned char *encryptedData = aesInstance.EncryptECB(ImgIn, nTaille, key);
  // unsigned char *encryptedData = aesInstance.EncryptCBC(ImgIn, nTaille, key,iv);
    unsigned char *encryptedData = aesInstance.EncryptCFB(ImgIn, nTaille, key,iv);

    for (unsigned int i = 0; i < nTaille; i++) {
        ImgOut[i] = (int)encryptedData[i] ;
    }



    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);
    delete[] encryptedData;
    free(ImgIn);
    free(ImgOut);

    return 0;
}
