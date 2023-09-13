#include "ImageBase.h"
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
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

    srand(key);
    const int size = imIn.getWidth() * imIn.getHeight();
    int *pixels = new int[size]; // Allouez dynamiquement de la mémoire

    for (int x = 0; x < imIn.getWidth(); ++x)
    {
        for (int y = 0; y < imIn.getHeight(); ++y)
        {
            int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
            pixels[j] = imIn[x][y];
        }
    }


    std::list<int> unusedPositions; // Créez une liste pour stocker les positions non utilisées
    for (int i = 0; i < size; ++i)
        unusedPositions.push_back(i); // Ajoutez tous les indices possibles à la liste

    int *permutedPixels = new int[size]; // Pixels permutés

    for (int i = 0; i < size; ++i)
    {
        // Choisir une position aléatoire parmi les non utilisées
        int randomPos = rand() % unusedPositions.size(); 

        // Utilisez un itérateur pour accéder à la position choisie
        auto it = std::next(unusedPositions.begin(), randomPos);
        int selectedPos = *it;

        // Assignez le pixel original à la nouvelle position permutée
        permutedPixels[selectedPos] = pixels[i];

        // Supprimez la position utilisée de la liste
        unusedPositions.erase(it);
    }

    // Copiez les valeurs modifiées dans l'image de sortie
    for (int x = 0; x < imIn.getWidth(); ++x)
    {
        for (int y = 0; y < imIn.getHeight(); ++y)
        {
            int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
            imOut[x][y] = permutedPixels[j];
        }
    }

    // Libérez la mémoire allouée dynamiquement
    delete[] pixels;
	delete permutedPixels;

	Entropie entropie;

	double entropy1 =  entropie.GetEntropieOfImage(imIn,128);

	std::cout << entropy1;

	double entropy2 =  entropie.GetEntropieOfImage(imOut,128);

	std::cout << entropy2;

    imOut.save(cNomImgEcrite);

    return 0;
}