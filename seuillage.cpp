#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.hpp"
#include "sobel.hpp"

ImageGris renormalise(ImageGris img) {
    int pixel_max=0;
    for (int y = 0; y < img.size(); y++) {
        for (int x = 0; x < img[y].size(); x++) {
            if (img[y][x] > pixel_max) {
                pixel_max = img[y][x];
            }
        }
    }

   
    if (pixel_max == 0) {
        return img; //image noir
    }

    
    for (int y = 0; y < img.size(); y++) {
        for (int x = 0; x < img[y].size(); x++) {
            img[y][x] = (img[y][x] * 255) / pixel_max;
        }
    }

    return img;
}

ImageGris seuillage(ImageGris img, int seuil) {
     if (seuil < 0) seuil = 0;
    if (seuil > 255) seuil = 255;
for(int i=0;i<img.size();i++){
for (int k=0;k<img[i].size();k++){
     if(img[i][k]<seuil)
            img[i][k]=255;
        else {
            img[i][k]=0;
        }
        
        
    }
}
    return img;
}


ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    int hauteur=imgIntensite.size();
    int largeur=imgIntensite[0].size();

    ImageGris imgResult(hauteur,vector<double>(largeur, 255));
      for(int y = 0; y < hauteur; y++) {
        for(int x = 0; x < largeur; x++) {
            bool voisinZero = false; // réinitialisation ici

            if(imgIntensite[y][x] >= seuil){
                if (y > 0 && imgContour[y-1][x] == 0) voisinZero = true;      
                if (y < hauteur-1 && imgContour[y+1][x] == 0) voisinZero = true; 
                if (x > 0 && imgContour[y][x-1] == 0) voisinZero = true;      
                if (x < largeur-1 && imgContour[y][x+1] == 0) voisinZero = true;
            }

            if (voisinZero) {
                imgResult[y][x] = 0; // pixel noir si voisin sélectionné
            }
        }
    }

    return imgResult;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
       ImageGris imgContour = seuillage(imgIntensite,seuilFort);

for (int i = 0; i < nbAmeliorations; i++)
    {
        // Seuillage faible
 ImageGris imgFaible = seuillage(imgIntensite, seuilFaible);

        // etendre le contour avec la première fonction doubleSeuillage
        imgContour = doubleSeuillage(imgFaible, imgContour, seuilFaible);
    }

    return imgContour;
}

