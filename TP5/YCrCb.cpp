#include <stdio.h>
#include "../image_ppm.h"

int clamp (int val) {
    if (val<0) {return 0;}
    else if (val>255) {return 255;}
    else return val;
}

int main(int argc, char* argv[]) {
    char cNomImgEcrite[250], cNomImgLueY[250], cNomImgLueCr[250], cNomImgLueCb[250];
    int nH, nW, nTaille, nR, nG, nB;
  
    if (argc != 5) {
       printf("Usage: ImageInY.pgm ImageInCr.pgm ImageInCb.pgm ImageOut.ppm\n"); 
       exit (1) ;
    }
    
    sscanf (argv[4],"%s",cNomImgEcrite) ;
    sscanf (argv[1],"%s",cNomImgLueY);
    sscanf (argv[2],"%s",cNomImgLueCr);
    sscanf (argv[3],"%s",cNomImgLueCb);

    OCTET *ImgOut, *ImgInY, *ImgInCr, *ImgInCb;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgOut, OCTET, 3*nTaille);

    allocation_tableau(ImgInY, OCTET, nTaille);
    allocation_tableau(ImgInCr, OCTET, nTaille);
    allocation_tableau(ImgInCb, OCTET, nTaille);

    lire_image_pgm(cNomImgLueY, ImgInY, nTaille);
    lire_image_pgm(cNomImgLueCr, ImgInCr, nTaille);
    lire_image_pgm(cNomImgLueCb, ImgInCb, nTaille);

    for (int i=0;i<nTaille*3;i+=3) {
        ImgOut[i]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128));
        ImgOut[i+1]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128));
        ImgOut[i+2]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128));
    }
    
    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgOut);free(ImgInY);free(ImgInCr);free(ImgInCb);

    return 0;
}