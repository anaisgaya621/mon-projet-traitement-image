#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
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

/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream flux;
    flux.open(cible);
    flux<<"P2"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<endl;
    flux<<255<<endl;
    for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            flux<<((int)img[i][j])<<" ";
            
    }
    flux<<endl;
    
    }
    flux.close();
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
      for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            int val =((int)img[i][j]);
            img[i][j]=255-val;
}
      }
    return img;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

