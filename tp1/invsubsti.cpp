#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

int main(int argc, char **argv)
{
	//utiliser numplot pour tracer hysto
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	int key;
  
	if (argc != 4) 
	{
		// clé entre 1 et 255
		printf("Usage: ImageIn.pgm 8_bits_key ImageOut.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%d",&key);
	sscanf (argv[3],"%s",cNomImgEcrite);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	const int size = imIn.getWidth() * imIn.getHeight();

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	srand(key);

	int randarray [size];
	int *pixels = new int[size];
	for(int i=0; i < size ; i++ ){
		randarray[i] = rand()%256;
	}

    for (int x = 0; x < imIn.getWidth(); ++x)
    {
        for (int y = 0; y < imIn.getHeight(); ++y)
        {
            int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
            pixels[j] = imIn[x][y];
        }
    }

	// on part du dernier pixel en bas a droite de l'image et on fait par ligne puis on passe a la ligne du dessus
	// en appliquant la formule pixel = (pixel - pixel de gauche - randarray[i])%256
	for(int i = size-1; i >= 0; i--){

		pixels[i] = (pixels[i] - pixels[i-1] - randarray[i])%256;

	}
		
	// Copiez les valeurs modifiées dans l'image de sortie
	for(int x = 0; x < imIn.getWidth(); ++x)
		for(int y = 0; y < imIn.getHeight(); ++y)
		{
			int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
			imOut[x][y] = pixels[j];
		}

	imOut.save(cNomImgEcrite);
		

	return 0;
}
