#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv)
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int key;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm 8_bits_key ImageOut.pgm \n");
        return 1;
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%s", cNomImgEcrite);

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

    for (int i = 0; i < size; ++i)
    {
        if (i == 0)
        {
            pixels[i] = ((rand() % 256) + pixels[i]) % 256;
        }
        else
        {
            pixels[i] = ((pixels[i - 1] + pixels[i]) + (rand() % 256)) % 256;
        }
    }

    // Copiez les valeurs modifiées dans l'image de sortie
    for (int x = 0; x < imIn.getWidth(); ++x)
    {
        for (int y = 0; y < imIn.getHeight(); ++y)
        {
            int j = y * imIn.getWidth() + x; // Calcul de l'indice correct
            imOut[x][y] = pixels[j];
        }
    }

    // Libérez la mémoire allouée dynamiquement
    delete[] pixels;

    imOut.save(cNomImgEcrite);

    return 0;
}
