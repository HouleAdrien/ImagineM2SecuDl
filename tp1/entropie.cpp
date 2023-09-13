#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "entropie.h"

Entropie::Entropie(){
	
}

double Entropie::GetEntropieOfImage(ImageBase &image, int i){

	const int nTaille = image.getWidth() * image.getHeight();

    std::cout<< "calcul de : "<< i <<std::endl ;

	int* pixels = new int[nTaille];

    for (int x = 0; x < image.getWidth(); ++x)
    {
        for (int y = 0; y < image.getHeight(); ++y)
        {
            int j = y * image.getWidth() + x;
            pixels[j] = image[x][y];
            
        }
    }

	int histo[256];
    double pourcentage = 0.98 * nTaille;

    for (int i = 0; i < 256; i++){
        histo[i] = 0;
    }

    for(int i = 0; i < nTaille; i++){
        histo[pixels[i]]++;
    }

    double entropie = 0;
    double temp;
    double pi;
    for(int i = 0; i < 256; i++){
        if(histo[i] == 0){
            temp = 0;
        }
        else{
            pi = double(histo[i])/nTaille;
            temp = pi * log2(pi);
            entropie -= temp;
        }
    }
    delete[] pixels;

    return entropie;

}
