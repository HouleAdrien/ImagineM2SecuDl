#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h> 
#include <list>
#include <iostream>
#include <algorithm>

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

	std::list<int> posAlreadyUsed;


	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	srand(key);

	for(int x = 0; x < imIn.getHeight(); ++x)


		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			int m = y*x;
			int newvalue;

			if( m == 0){
				 newvalue = rand();
			}else{
				 newvalue = rand() % (m);
			}
			

			if(std::find(posAlreadyUsed.begin(), posAlreadyUsed.end(), m) != posAlreadyUsed.end()){

				//while(std::find(posAlreadyUsed.begin(), posAlreadyUsed.end(), m) != posAlreadyUsed.end()){
					m =m+1;
				//}

				newvalue = rand() % (m);
				imOut[x][y] = newvalue;

			}else{
				imOut[x][y] = newvalue;
				posAlreadyUsed.push_back(m);
			}

		}
		
	imOut.save(cNomImgEcrite);




	return 0;
}
