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

	Entropie entropie;
	double entropy1 =  entropie.GetEntropieOfImage(imIn,128);
	std::cout << entropy1;
	double entropy2 =  entropie.GetEntropieOfImage(imOut,128);
	std::cout << entropy2;

	imOut.save(cNomImgEcrite);

	return 0;
}
