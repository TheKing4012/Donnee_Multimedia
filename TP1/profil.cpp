// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, nTaille;
    int profil[256];
    int param;
    int num;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm Colonne?\n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%i",&param) ;
    sscanf (argv[3],"%i",&num) ;


    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    for (int i = 0; i < 256; i++) {
        profil[i] = 0;
    }

    if(param == 1) {
        for (int y = 0; y < nH; y++) { //POUR CHAQUE LIGNE
            profil[y] += ImgIn[y * nW + num];
        }
    } else {
        for (int j = 0; j < nW; j++) { //POUR CHAQUE COLONNE
            profil[j] += ImgIn[num * nW + j];
        }
    }

    for (int i = 0; i < 256; i++) {
        printf("%i %i\n", i, profil[i]);
    }

    return 1;
}
