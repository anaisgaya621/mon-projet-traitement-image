#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.hpp"
#include "ppm.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

Image lirePPM(string source) {

    ifstream ppm;
    ppm.open(source);

    if (!ppm)
        throw runtime_error("Fichier non trouve: " + source);

    string type;
    int height;
    int width;
    int MAX_VALUE;

    // Lecture du type doit etre en prmiere position 
    ppm >> type;

    // Sauter les commentaires eventuels
    while (ppm.peek() == '#') {    
        string ligne;
        getline(ppm, ligne);  // ignore la ligne
    }

    // le lecture de la dimension 
    ppm >> width;
    ppm >> height;
    ppm >> MAX_VALUE;

    // Verifier le type PPM
    if (type != "P3")
        throw runtime_error("Fichier n'est pas de type P3: " + source);

    //declaration using la methode du cours 
    Image tableau_Color;//declaration
    tableau_Color = Image(height);         // 

    for (int k = 0; k < height; k++) {
        tableau_Color[k] = vector<Couleur>(width);  // allocation des colonnes
    }

  
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            int r, g, b;
            if (!(ppm >> r >> g >> b))
                throw runtime_error("Impossible de lire les valeurs RGB dans " + source);

            // Affectation dans la structure RED GREEM BLUE 
            tableau_Color[i][j].r = r;
            tableau_Color[i][j].g = g;
            tableau_Color[i][j].b = b;
        }
    }

    ppm.close();
    return tableau_Color;
}
  
    



    

/**  Écrit une image dans un fichier PPM
 * @param img une image
 * @param cible le nom d'un fichier PPM
 **/

void ecrirePPM(Image img, string cible) {
    ofstream ppm(cible);
    ppm << "P3" << endl;
    ppm << img[0].size() << " " << img.size() << endl;  // width height
    ppm << 255 << endl; // valeur max standard

    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            ppm << (int)img[i][j].r << " "
                << (int)img[i][j].g << " "
                << (int)img[i][j].b << "\n"; // <- un saut de ligne pour chaque pixel
        }
    }
    ppm.close();
}


