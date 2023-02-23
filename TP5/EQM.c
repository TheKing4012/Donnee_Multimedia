// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "../image_ppm.h"

int indiceImage(int x, int y, int width) {
    return x * width + y;
}

OCTET* dilatation(int nH, int nW, OCTET *ImgIn) {
    OCTET *ImgOut;
    allocation_tableau(ImgOut, OCTET, nH * nW);
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            OCTET monPixel = ImgIn[indiceImage(i, j, nW)];

            if (i == 0 && j == 0 &&
                (ImgIn[indiceImage(i + 1, j, nW)] == 0 || ImgIn[indiceImage(i, j + 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (i == 0 && j == nW - 1 &&
                       (ImgIn[indiceImage(i + 1, j, nW)] == 0 || ImgIn[indiceImage(i, j - 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (i == nH - 1 && j == 0 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 0 || ImgIn[indiceImage(i, j + 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (i == nH - 1 && j == nW - 1 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 0 || ImgIn[indiceImage(i, j - 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (i == 0 && (ImgIn[indiceImage(i + 1, j, nW)] == 0 || ImgIn[indiceImage(i, j + 1, nW)] == 0 ||
                                  ImgIn[indiceImage(i, j - 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (j == 0 && (ImgIn[indiceImage(i + 1, j, nW)] == 0 || ImgIn[indiceImage(i, j + 1, nW)] == 0 ||
                                  ImgIn[indiceImage(i - 1, j, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (i == nH - 1 &&
                       (ImgIn[indiceImage(i - 1, j, nW)] == 0 || ImgIn[indiceImage(i, j + 1, nW)] == 0 ||
                        ImgIn[indiceImage(i, j - 1, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else if (j == nW - 1 &&
                       (ImgIn[indiceImage(i, j - 1, nW)] == 0 || ImgIn[indiceImage(i + 1, j, nW)] == 0 ||
                        ImgIn[indiceImage(i - 1, j, nW)] == 0)) {
                ImgOut[indiceImage(i, j, nW)] = 0;
            } else {
                if (ImgIn[indiceImage(i + 1, j, nW)] == 0 || ImgIn[indiceImage(i - 1, j, nW)] == 0 ||
                    ImgIn[indiceImage(i, j + 1, nW)] == 0 || ImgIn[indiceImage(i, j - 1, nW)] == 0) {
                    ImgOut[indiceImage(i, j, nW)] = 0;
                } else {
                    ImgOut[indiceImage(i, j, nW)] = ImgIn[indiceImage(i, j, nW)];
                }
            }
        }
    }

    return ImgOut;
}

OCTET* erosion(int nH, int nW, OCTET *ImgIn) {
    OCTET *ImgOut;
    allocation_tableau(ImgOut, OCTET, nH * nW);
    for (int i = 0; i < nH; i++) {
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

    return ImgOut;
}



int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250], cNomImgLue2[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n");
        exit (1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgLue2) ;

    OCTET *ImgIn, *ImgIn2;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }

    int nbr = 0;
    int diff = 0;
    for (int i=0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (ImgIn[indiceImage(i, j, nW)] != ImgIn2[indiceImage(i, j, nW)]) {
                nbr++;
                diff += pow((ImgIn[indiceImage(i, j, nW)] - ImgIn2[indiceImage(i, j, nW)]),2);
            }
        }
    }

    //ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    printf("\n Nombre de pixels différents: %d\n",nbr);
    printf("\n Valeur de la différence: %d\n",diff/nTaille);
    free(ImgIn);
    free(ImgIn2);

    return 1;
}
