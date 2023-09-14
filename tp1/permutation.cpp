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


    std::list<int> unusedPositions; // Créez une liste pour stocker les positions non utilisées
    for (int i = 0; i < nTaille; ++i)
        unusedPositions.push_back(i); // Ajoutez tous les indices possibles à la liste

    int *permutedPixels = new int[nTaille]; // Pixels permutés

    for (int i = 0; i < nTaille; ++i)
    {
        // Choisir une position aléatoire parmi les non utilisées
        int randomPos = rand() % unusedPositions.size(); 

        // Utilisez un itérateur pour accéder à la position choisie
        auto it = std::next(unusedPositions.begin(), randomPos);
        int selectedPos = *it;

        // Assignez le pixel original à la nouvelle position permutée
        permutedPixels[selectedPos] = ImgIn[i];

        // Supprimez la position utilisée de la liste
        unusedPositions.erase(it);
    }

    // Copiez les valeurs modifiées dans l'image de sortie
    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[i] = permutedPixels[i];
    }


	delete permutedPixels;

	Entropie entropie;

	double entropy1 =  entropie.GetEntropieOfImage(ImgIn,nTaille);

	std::cout << entropy1;

	double entropy2 =  entropie.GetEntropieOfImage(ImgOut,nTaille);

	std::cout << entropy2;

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}