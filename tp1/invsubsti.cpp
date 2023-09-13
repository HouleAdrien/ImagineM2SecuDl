#include "ImageBase.h"
#include <iostream>
#include <limits>
#include <cstdlib>  // Pour rand
#include <ctime>    // Pour time
#include "entropie.h"

int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250], cNomImgFor[250]; // Ajoutez cNomImgFor pour l'image de vérification

    if (argc != 3) 
    {
        std::cout << "Usage: ImageIn.pgm ImageOut.pgm" << std::endl; 
        return 1;
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    ImageBase imIn;
    imIn.load(cNomImgLue);


    const int size = imIn.getWidth() * imIn.getHeight();

    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());


    Entropie entropie;

    int randarray[size];
	

    double minEntropy = 10;
    int bestKey = 0;

for (int k = 1; k < 256; k++) {
	int *pixels = new int[size];
     int currentKey = k; // Stockez la valeur actuelle de k

     srand(currentKey); // Utilisez currentKey pour initialiser srand

	 for(int i=0; i < size ; i++ ){
		randarray[i] = rand()%256;
	}

    // // Créez une copie de l'image originale à chaque itération
     ImageBase currentImage(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	 for(int x = 0; x < imIn.getWidth(); ++x)
		for(int y = 0; y < imIn.getHeight(); ++y) {
			int j = y * imIn.getWidth() + x; // Calcul de l'indice
			pixels[j] = imIn[x][y];
    }

	 for(int i = size-1; i >= 0; i--){

			pixels[i] = (pixels[i] - pixels[i-1] - randarray[i])%256;

		}

	for(int x = 0; x < imIn.getWidth(); ++x)
			for(int y = 0; y < imIn.getHeight(); ++y)
			{
				int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
				currentImage[x][y] = pixels[j];
			}


    	 double entropy =  entropie.GetEntropieOfImage(currentImage,k);

		std::cout << "Key " << currentKey << " Entropy: " << entropy << std::endl;
		delete[] pixels;
		if (entropy < minEntropy) {
			minEntropy = entropy;
			bestKey = currentKey;
		}
	}

	int *pixels = new int[size];
	srand(bestKey); 

	 for(int i=0; i < size ; i++ ){
		randarray[i] = rand()%256;
	}

	 for(int x = 0; x < imIn.getWidth(); ++x)
		for(int y = 0; y < imIn.getHeight(); ++y) {
			int j = y * imIn.getWidth() + x; // Calcul de l'indice
			pixels[j] = imIn[x][y];
    }

	 for(int i = size-1; i >= 0; i--){

			pixels[i] = (pixels[i] - pixels[i-1] - randarray[i])%256;

		}

	for(int x = 0; x < imIn.getWidth(); ++x)
		for(int y = 0; y < imIn.getHeight(); ++y)
		{
			int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
			imOut[x][y] = pixels[j];
		}


    std::cout << "Best Key: " << bestKey << " Best Entropy: " << minEntropy << std::endl;

    // Sauvegardez l'image restaurée avec la meilleure clé
    imOut.save(cNomImgEcrite);

	delete[] pixels;

    return 0;
}
