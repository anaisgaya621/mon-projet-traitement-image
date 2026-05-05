#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.hpp"
#include "pgm.hpp"



ImageGris lirePGM(string source) {
   ifstream pgm;
pgm.open(source);
if (not pgm)
    throw runtime_error("Fichier non trouve: "+source);
    while (pgm.peek() == '#') {
        pgm.ignore(1000, '\n'); // ignore la ligne de commentaire
    }
    string type;
    int width;
    int height;
    int MAX_VAL;
    ImageGris img;

     pgm >> type;
    if (type != "P2")
        throw runtime_error("Format PGM invalide (attendu P2)");

    pgm >> width >> height;
    pgm >> MAX_VAL;
    img.resize(height);
     for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int val;
            if (!(pgm >> val))
                throw runtime_error("Erreur de lecture : pixels manquants");
            img[i].push_back(val);
        }
    }
    
    pgm.close();
    return img;
}

void ecrirePGM(ImageGris img, string cible) {
        ofstream flux;
    flux.open(cible);
    flux<<"P2"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<endl;
    flux<<255<<endl;
    for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
           int val=((int)img[i][j]);
            if(val>255)val=255;
            if(val<0) val=0;
            flux<<val<<" ";
            
    }
    flux<<endl;
    
    }
    flux.close();
   
}

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) { 
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
   
}

ImageGris inversePGM(ImageGris img) {
     for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            int val =((int)img[i][j]);
            img[i][j]=255-val;
}
      }
    return img;
}

