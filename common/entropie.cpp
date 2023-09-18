#include <math.h>
#include "entropie.h"

Entropie::Entropie(){
	
}

double Entropie::GetEntropieOfImage(OCTET *image, int nTaille){


    int histo[256];
    double pourcentage = 0.98 * nTaille;

    for (int i = 0; i < 256; i++){
        histo[i] = 0;
    }

    for(int i = 0; i < nTaille; i++){
        histo[image[i]]++;
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

    return entropie;

}
