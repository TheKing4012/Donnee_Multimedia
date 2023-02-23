#include <stdio.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcriteY[250], cNomImgEcriteCr[250], cNomImgEcriteCb[250];
    int nH, nW, nTaille, nR, nG, nB;
  
    if (argc != 5) {
       printf("Usage: ImageIn.ppm ImageOutY.pgm ImageOutCr.pgm ImageOutCb.pgm\n"); 
       exit (1) ;
    }
   
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcriteY);
    sscanf (argv[3],"%s",cNomImgEcriteCr);
    sscanf (argv[4],"%s",cNomImgEcriteCb);

    OCTET *ImgIn, *ImgOutY, *ImgOutCr, *ImgOutCb;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, 3*nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    
    allocation_tableau(ImgOutY, OCTET, nTaille);
    allocation_tableau(ImgOutCr, OCTET, nTaille);
    allocation_tableau(ImgOutCb, OCTET, nTaille);

    for (int i=0;i<3*nTaille;i+=3) {
        nR = ImgIn[i];
        nG = ImgIn[i+1];
        nB = ImgIn[i+2];
        ImgOutY[i/3]=0.299*nR+0.587*nG+0.114*nB;
        ImgOutCr[i/3]=0.5*nR-0.4187*nG-0.0813*nB+128;
        ImgOutCb[i/3]=-0.1687*nR-0.3313*nG+0.5*nB+128;
    }
    ecrire_image_pgm(cNomImgEcriteY, ImgOutY, nH, nW);
    ecrire_image_pgm(cNomImgEcriteCr, ImgOutCr, nH, nW);
    ecrire_image_pgm(cNomImgEcriteCb, ImgOutCb, nH, nW);
    free(ImgIn);free(ImgOutY);free(ImgOutCr);free(ImgOutCb);

    return 0;
}