#include <stdio.h>
#include "../image_ppm.h"

int clamp (int val) {
    if (val<0) {return 0;}
    else if (val>255) {return 255;}
    else return val;
}

int main(int argc, char* argv[]) {
    char cNomImgEcrite[250], cNomImgLueY[250], cNomImgLueCr[250], cNomImgLueCb[250], param[250];
    int nH, nW, nTaille, nR, nG, nB, formula;
  
    if (argc != 6) {
       printf("Usage: ImageInY.pgm ImageInCr.pgm ImageInCb.pgm ImageOut.ppm RGB|RBG|BRG|BGR|GRB|GRB\n");
       exit (1) ;
    }
    
    sscanf (argv[4],"%s",cNomImgEcrite) ;
    sscanf (argv[1],"%s",cNomImgLueY);
    sscanf (argv[2],"%s",cNomImgLueCr);
    sscanf (argv[3],"%s",cNomImgLueCb);
    sscanf (argv[5],"%s",param);

    if(strcmp(param,"RGB") == 0) {
        formula = 1;
    } else if (strcmp(param,"RBG") == 0) {
        formula = 2;
    } else if (strcmp(param,"BRG") == 0) {
        formula = 3;
    } else if (strcmp(param,"BGR") == 0) {
        formula = 4;
    } else if (strcmp(param,"GRB") == 0) {
        formula = 5;
    } else if (strcmp(param,"GBR") == 0) {
        formula = 6;
    } else {
        printf("Mauvais pamaètres en 4eme position \n");
        exit(1);
    }

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

        switch (formula) {
            case 1:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); //R
                    ImgOut[i+1]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); // G
                    ImgOut[i+2]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); // B
                }
                break;
            case 2:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); // R
                    ImgOut[i+1]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); // B
                    ImgOut[i+2]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); // G
                }
                break;
            case 3:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); //B
                    ImgOut[i+1]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); //G
                    ImgOut[i+2]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); //R
                }
                break;
            case 4:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); //B
                    ImgOut[i+1]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); //R
                    ImgOut[i+2]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); //G
                }
                break;
            case 5:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); //G
                    ImgOut[i+1]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); //R
                    ImgOut[i+2]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); //B
                }
                break;
            case 6:
                for (int i=0;i<nTaille*3;i+=3) {
                    ImgOut[i]= clamp(ImgInY[i/3]-0.34414*(ImgInCb[i/3]-128)-0.714414*(ImgInCr[i/3]-128)); //G
                    ImgOut[i+1]= clamp(ImgInY[i/3]+1.772*(ImgInCb[i/3]-128)); //B
                    ImgOut[i+2]= clamp(ImgInY[i/3]+1.402*(ImgInCr[i/3]-128)); //R
                }
                break;
        }
    
    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgOut);free(ImgInY);free(ImgInCr);free(ImgInCb);

    return 0;
}