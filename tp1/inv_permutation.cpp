#include <stdio.h>
#include <stdlib.h> 
#include <list>
#include <iostream>
#include <algorithm>
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
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%d",&key);
    sscanf (argv[3],"%s",cNomImgEcrite);

    OCTET *ImgIn;
    OCTET *ImgOut;

    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);

    srand(key);

    std::list<int> positions; // Créez une liste pour stocker les positions originales des pixels après la permutation
    for (int i = 0; i < nTaille; ++i)
        positions.push_back(i);

    int *permutedPositions = new int[nTaille]; // Positions originales après la permutation

    for (int i = 0; i < nTaille; ++i)
    {
        // Choisir une position aléatoire parmi les non utilisées
        int randomPos = rand() % positions.size();

        auto it = std::next(positions.begin(), randomPos);
        int selectedPos = *it;

        permutedPositions[selectedPos] = i;

        positions.erase(it);
    }

    // Utilisez le mappage pour dé-permuter les pixels
    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[permutedPositions[i]] = ImgIn[i];
    }

    delete[] permutedPositions;

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
