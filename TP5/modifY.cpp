#include <stdio.h>
#include "../image_ppm.h"

int clamp (int val) {
    if (val<0) {return 0;}
    else if (val>255) {return 255;}
    else return val;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcriteY[250];
    int nH, nW, nTaille, nR,k;
  
    if (argc != 4) {
       printf("Usage: ImageIn.ppm ImageOutY.pgm ImageOutCr.pgm ImageOutCb.pgm\n"); 
       exit (1) ;
    }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcriteY);
    sscanf (argv[3],"%d",&k);

    if(k < -128 || k > 128) {
        printf("Valeur de k incorrecte\n");
        exit(1);
    }

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
        {
            ImgOut[i*nW+j]= clamp(ImgIn[i*nW+j] + k);
        }
    ecrire_image_pgm(cNomImgEcriteY, ImgOut, nH, nW);
    free(ImgIn);free(ImgOut);

    return 0;
}