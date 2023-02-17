// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "../image_ppm.h"

int pre_seuil(OCTET* ImgIn,int i, int j, int nW, int SB, int SH) {
    return ImgIn[i * nW + j] <= SB ? 0 : ImgIn[i * nW + j] >= SH ? 255 : ImgIn[i * nW + j];
}

int hyst(OCTET* ImgIn,int i, int j, int nW, int SB, int SH) {
    if(ImgIn[i*nW+j] > SB && ImgIn[i*nW+j] < SH) {
        if(ImgIn[(i+1)*nW+j] == 255 || ImgIn[(i-1)*nW+j] == 255 ||ImgIn[i*nW+j+1] == 255 || ImgIn[i*nW+j-1] ||
                ImgIn[(i+1)*nW+j+1] == 255 || ImgIn[(i+1)*nW+j-1] == 255 || ImgIn[(i-1)*nW+j+1] == 255 || ImgIn[(i-1)*nW+j-1] == 255) {
            return 255;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, SB, SH;

    if (argc != 5)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm SB SH \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&SB);
    sscanf (argv[4],"%d",&SH);

    OCTET *ImgIn, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);

    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }


    for (int i=0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[i * nW + j] = pre_seuil(ImgIn, i, j, nW, SB, SH);
        }
    }

    for (int i=0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut2[i * nW + j] = hyst(ImgOut, i, j, nW, SB, SH);
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut2,  nH, nW);
    free(ImgIn); free(ImgOut); free(ImgOut2);

    return 1;
}
