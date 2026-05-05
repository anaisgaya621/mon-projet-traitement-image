#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

/// BEGIN griscouleurh

/** Transforme une image couleur en une image en teintes de gris
 * @param img une image
 * @return une image en teintes de gris
 **/
//0.2126∗r+0.7152∗g+0.0722∗b.
ImageGris CouleurAuGris( Image img ) {
   ImageGris grise;
    grise=ImageGris(img.size());
    for(int i=0;i<img.size();i++){
    grise[i]=vector<double>(img[0].size());
}
    for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            grise[i][j]=img[i][j].r*0.2126+img[i][j].g*0.7152+img[i][j].b*0.0722;
        }
    }
    return grise;}
    
    

/** Transforme une image en teintes de gris en une image en couleurs (mais grise)
 * @param img une image en teintes de gris
 * @return une image
 **/

Image GrisACouleur( ImageGris img ) {
    Image Color;//declaratiom
    Color=Image(img.size());//allocation
    for(int k=0;k<img.size();k++){
        Color[k]=vector<Couleur>(img[0].size());
    }
    for(int i=0;i<img.size();i++){
        for(int k=0;k<img[i].size();k++){
            Color[i][k].r = img[i][k];
            Color[i][k].g = img[i][k];
            Color[i][k].b = img[i][k];
            
        }
    }
    return Color;
}

