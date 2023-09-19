#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int N = 256;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   int T[N][2];
   for(int i=0; i<N; i++){
     T[i][0]=i;
     T[i][1]=0;
   }

  for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++){
      T[ImgIn[i*nW+j]][1]++;
    }
  }

  std::ofstream ofs ("histo.dat", std::ofstream::out);

  for(int i=0; i < N; i++)
  {
    ofs<<T[i][0]<<"  "<<T[i][1]<<"\n";
  }

  ofs.close();


   return 1;
}