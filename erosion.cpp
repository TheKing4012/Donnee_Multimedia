// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width) {
    return x * width + y;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }


    for (int i=0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            OCTET monPixel = ImgIn[indiceImage(i, j, nW)];

            if (i == 0 && j == 0 &&
                (ImgIn[indiceImage(i + 1, j, nW)] == 255 || ImgIn[indiceImage(i, j + 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (i == 0 && j == nW - 1 &&
                       (ImgIn[indiceImage(i + 1, j, nW)] == 255 || ImgIn[indiceImage(i, j - 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (i == nH - 1 && j == 0 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 255 || ImgIn[indiceImage(i, j + 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (i == nH - 1 && j == nW - 1 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 255 || ImgIn[indiceImage(i, j - 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (i == 0 && (ImgIn[indiceImage(i + 1, j, nW)] == 255 || ImgIn[indiceImage(i, j + 1, nW)] == 255 ||
                                  ImgIn[indiceImage(i, j - 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (j == 0 && (ImgIn[indiceImage(i + 1, j, nW)] == 255 || ImgIn[indiceImage(i, j + 1, nW)] == 255 ||
                                  ImgIn[indiceImage(i - 1, j, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (i == nH - 1 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 255 || ImgIn[indiceImage(i, j + 1, nW)] == 255 ||
                        ImgIn[indiceImage(i, j - 1, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else if (j == nW - 1 &&
                       (ImgIn[indiceImage(i, j - 1, nW)] == 255 || ImgIn[indiceImage(i + 1, j, nW)] == 255 ||
                        ImgIn[indiceImage(i - 1, j, nW)] == 255)) {
                ImgOut[indiceImage(i, j, nW)] = 255;
            } else {
                if (ImgIn[indiceImage(i + 1, j, nW)] == 255 || ImgIn[indiceImage(i - 1, j, nW)] == 255 ||
                    ImgIn[indiceImage(i, j + 1, nW)] == 255 || ImgIn[indiceImage(i, j - 1, nW)] == 255) {
                    ImgOut[indiceImage(i, j, nW)] = 255;
                } else {
                    ImgOut[indiceImage(i, j, nW)] = ImgIn[indiceImage(i, j, nW)];
                }
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
