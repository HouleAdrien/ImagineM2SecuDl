#include "../common/image_ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

unsigned char* generateRandomSequence(int nTaille){
    unsigned char *out;
    allocation_tableau(out, unsigned char, nTaille);

      for (int i = 0; i < nTaille; i++) {
        if(rand()%2 == 0){
            out[i] = 0;
        }else{
            out[i] = 1;
        }
    }

    return out;
}

unsigned char* extractMessage(OCTET* Img,int nTaille, int k){
    unsigned char *out;
    allocation_tableau(out, unsigned char, nTaille);
      for (int i = 0; i < nTaille; i++) {
        out[i] = ((Img[i] & (1 << k)) >> k);
    }

    return out;
}

void extrairePlanBinaire(OCTET* ImgIn, OCTET* ImgOut, int nTaille, int k) {
    for (int i = 0; i < nTaille; i++) {
        ImgOut[i] = ((ImgIn[i] & (1 << k)) >> k)*255; // Masquage binaire pour récupérer le bit à la position k
    }
}

void insererMessageBinaire(OCTET* imgin,OCTET* imgout,unsigned char* message,int nTaille, int k){
     for (int i = 0; i < nTaille; i++) {
        imgout[i] = imgin[i];
        //remise a zéro du bit position k
        imgout[i] &= ~(1 <<k);

        //on insert notre message à la position
        imgout[i] |= (message[i] << k);
     }
}

unsigned char* textToBinary(const std::string& text) {

    unsigned char *binary = new unsigned char[text.length() * 8];
    int index = 0;
    for(char c : text) {
        for(int i = 7; i >= 0; i--) {
            binary[index++] = (c & (1 << i)) ? 1 : 0;
        }
    }
    return binary;
}

std::string binaryToText(unsigned char* binary, int length) {
    std::string text;
    for(int i = 0; i < length; i+=8) {
        char c = 0;
        for(int j = 0; j < 8; j++) {
            if(binary[i+j]) {
                c |= (1 << (7-j));
            }
        }
        text += c;
    }
    return text;
}


int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250], cNomImgEcrite2[250], cNomFichierTexte[250];
    int k;

    if (argc != 5)
    {
        printf("Usage: ImageIn.pgm ImageLsb.pgm ImageMsb.pgm fichierTexte.txt\n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%s", cNomImgEcrite2);
    sscanf(argv[4], "%s", cNomFichierTexte);

    std::ifstream file(cNomFichierTexte);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::cout << content.length() * 8;
    unsigned char *message = textToBinary(content);    

    OCTET *ImgIn;
    OCTET *ImgOut;
    OCTET *ImgOut2;



    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);


    insererMessageBinaire(ImgIn,ImgOut,message,nTaille,0);
    insererMessageBinaire(ImgIn,ImgOut2,message,nTaille,7);

    unsigned char *extracted  = extractMessage(ImgOut,nTaille,0);

    std::string extractedText = binaryToText(extracted, nTaille);

    std::ofstream outFile("extracted.txt");
    outFile << extractedText;
    outFile.close();    

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    ecrire_image_pgm(cNomImgEcrite2, ImgOut2, nH, nW);

    free(ImgIn);
    free(ImgOut);
    free(ImgOut2);
    delete[] message;
    free(extracted);

    return 0;
}