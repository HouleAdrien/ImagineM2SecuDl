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

    OCTET *ImgIn;
    OCTET *ImgOut;

    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);


    Entropie entropie;
	const int taille = nTaille;
    int *randarray = (int *)malloc(nTaille * sizeof(int));
	

    double minEntropy = 10;
    int bestKey = 0;

	for (int k = 1; k < 256; k++) {
     	int currentKey = k; // Stockez la valeur actuelle de k

		OCTET *currentImage;
		allocation_tableau(currentImage, OCTET, nTaille);
    	lire_image_pgm(cNomImgLue, currentImage, nH * nW);

		srand(currentKey); // Utilisez currentKey pour initialiser srand

			for(int i=0; i < nTaille ; i++ ){
				randarray[i] = rand()%256;
			}


			for(int i = nTaille-1; i >= 0; i--){

				currentImage[i] = (currentImage[i] - currentImage[i-1] - randarray[i])%256;

			}



			double entropy =  entropie.GetEntropieOfImage(currentImage,nTaille);

			std::cout << "Key " << currentKey << " Entropy: " << entropy << std::endl;
			free(currentImage);
			if (entropy < minEntropy) {
				minEntropy = entropy;
				bestKey = currentKey;
			}
	}

	srand(bestKey); 

	 for(int i=0; i < nTaille ; i++ ){
		randarray[i] = rand()%256;
	}


	 for(int i = nTaille-1; i >= 0; i--){

			ImgOut[i] = (ImgIn[i] - ImgIn[i-1] - randarray[i])%256;

		}


    std::cout << "Best Key: " << bestKey << " Best Entropy: " << minEntropy << std::endl;

    // Sauvegardez l'image restaurée avec la meilleure clé
    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH , nW);

	free(ImgIn);
	free(ImgOut);
	free(randarray);
    return 0;
}
