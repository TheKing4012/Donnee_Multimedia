// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "../image_ppm.h"

int width =  0;

int process(OCTET *ImgIn, int x, int y, int nW) {
    return (ImgIn[x * nW + y] + ImgIn[(x-3) * nW + y] + ImgIn[(x+3) * nW + y] + ImgIn[(x+3) * nW + (y+3)] + ImgIn[(x+3) * nW + (y-3)] + ImgIn[(x-3) * nW + (y-3)] + ImgIn[(x-3) * nW + (y+3)]   + ImgIn[x * nW + (y-3)] + ImgIn[x * nW + (y+3)]) / 9.0;
}

int pos(int x, int y,  int c) {
    return 3*y*width + 3*x + c;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    width = nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i=3; i < 3*nH-3 ; i++) {
        for (int j = 3; j < 3*nW-1; j++) {
            ImgOut[i * nW + j] = process(ImgIn,i,j,nW);
        }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
}