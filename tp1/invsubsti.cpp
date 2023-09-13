#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include "entropie.h"

int main(int argc, char **argv)
{
	//utiliser numplot pour tracer hysto
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	int key;
  
	if (argc != 3) 
	{
		// clé entre 1 et 255
		printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	const int size = imIn.getWidth() * imIn.getHeight();

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	ImageBase images[255];

	for(int i=0; i < 255; i ++){
		images[i] = imOut;
	}
	Entropie entropie;

	int randarray [size];
	int *pixels = new int[size];

    for (int x = 0; x < imIn.getWidth(); ++x)
    {
        for (int y = 0; y < imIn.getHeight(); ++y)
        {
            int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
            pixels[j] = imIn[x][y];
        }
    }

    for(int k=0; k < 255;k++){

    	srand(k+1);

    	for(int i=0; i < size ; i++ ){
			randarray[i] = rand()%256;
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
				images[k][x][y] = pixels[j];
			}

    }

    double maxeentro = -1;
    int keymaxentro = 0;

    for(int i=0; i < 255; i ++){
    	double res = entropie.GetEntropieOfImage(images[i]);
		std::cout << res ;
	}


	

	imOut.save(cNomImgEcrite);
	delete[] pixels;


	return 0;
}

