#include <stdio.h>
#include "image_ppm.h"

int filtre(OCTET *ImgIn,int nW,int t[9],int x,int y) {
    int res=0;
    res+=t[0]*ImgIn[(x-1)*nW+y-1];
    res+=t[1]*ImgIn[(x-1)*nW+y];
    res+=t[2]*ImgIn[(x-1)*nW+y+1];
    res+=t[3]*ImgIn[x*nW+y-1];
    res+=t[4]*ImgIn[x*nW+y];
    res+=t[5]*ImgIn[x*nW+y+1];
    res+=t[6]*ImgIn[(x+1)*nW+y-1];
    res+=t[7]*ImgIn[(x+1)*nW+y];
    res+=t[8]*ImgIn[(x+1)*nW+y+1];
    return res/(t[0]+t[1]+t[2]+t[3]+t[4]+t[5]+t[6]+t[7]+t[8]);
}

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    if (argc != 3) {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n");
       exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int carre[] = {1,4,1,4,8,4,1,4,1}; //il te suffit de changer les coeffs par des 1 partout pour avoir le filtre moyenneur

    for (int i=1; i < nH-1; i++) {
        for (int j=1; j < nW-1; j++) {
            ImgOut[i*nW+j] = filtre(ImgIn,nW,carre,i,j);
        }
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);
   return 0;
}