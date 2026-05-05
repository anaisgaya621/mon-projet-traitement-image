#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"

ImageGris intensiteH(ImageGris img) {
   ImageGris res(img.size(), vector<double>(img[0].size(),0));
    for(int i=1;i<img.size()-1;i++){
        for(int j=1;j<img[i].size()-1;j++){
            res[i][j]=img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1]
- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
        }
    }
    return res;
}

ImageGris intensiteV(ImageGris img) {
       ImageGris res(img.size(), vector<double>(img[0].size(),0));
    for(int i=1;i<img.size()-1;i++){
         
        for(int j=1;j<img[i].size()-1;j++){
            res[i][j]=img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1]
- img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
        }
    }
    return res;
   
}

ImageGris intensite(ImageGris img) {
   ImageGris h = intensiteH(img);
    ImageGris v = intensiteV(img);
    ImageGris resultat(img.size(),vector<double>(img[0].size(),0));

    
    for(int i = 1; i < img.size()-1; i++) {
        for(int j = 1; j < img[i].size()-1; j++) {
            resultat[i][j]=( sqrt(pow(h[i][j],2) +pow( v[i][j],2)));
        }
    }
    return resultat;
}

