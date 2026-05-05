
#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;


/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};


/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensiteH(ImageGris img) {
    ImageGris res(img.size(), vector<double>(img[0].size(), 0));
   for(int i =1;i<img.size()-1;i++){
       for(int j=1;j<img[i].size()-1;j++){
          res[i][j]= img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1]
- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
       }
       
   }
    return res;
}
ImageGris intensiteV(ImageGris img) {
    ImageGris res(img.size(), vector<double>(img[0].size(), 0));
    for(int i =1;i<img.size()-1;i++){
       for(int j=1;j<img[i].size()-1;j++){
          res[i][j]=img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1]
- img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
       }
       
   }
    return res;
}

ImageGris intensite(ImageGris img) {
   int height=img.size();
    int width=img[0].size();
    ImageGris H=intensiteH(img);
    ImageGris V=intensiteV(img);
    ImageGris res(height, vector<double>(width, 0));
    for(int i =1;i<img.size()-1;i++){
       for(int j=1;j<img[i].size()-1;j++){
          res[i][j]=sqrt(H[i][j]*H[i][j]+V[i][j]*V[i][j]);
       }
       
   }
    return res;
}


/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
       ImageGris img;
    ifstream pgm;
    pgm.open(source);
    while (pgm.peek() == '#') {  // peek() regarde le prochain caractère
    string ligne;
    getline(pgm, ligne);     // lit et ignore la ligne entière
}
    if (not pgm)
        throw runtime_error("Fichier non trouve: "+source);
    string type;
    int width;
    int height;
    int valeur_max;
    int k;
    pgm>>type;
    pgm>>width;
    pgm>>height;
    pgm>>valeur_max;

    if(type!="P2")
         throw runtime_error("Fichier n' est pas de type pgm: "+source);
        
       
        
    
    img.resize(height);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(!(pgm>>k)){
                throw runtime_error("impossible de lire "+source);
            }
            if (k < 0 || k > valeur_max)
                throw runtime_error("Valeur de pixel invalide à " + to_string(i) + "," +to_string(j) + " dans " + source);
                    
            img[i].push_back(((int)k));
        }
    }
     pgm.close();   
    return img;
        
}



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

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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


/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
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

void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
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

/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    //si dans la matrice de imgContour on a 0 pixel selectionne et si c 255 pixel non selectionne
    
    ImageGris out = imgContour;//creation d'un copie 
   if (seuil < 0) seuil = 0;
    if (seuil > 255) seuil = 255;
    for(int i=0;i<imgIntensite.size();i++){
    for(int j=0;j<imgIntensite[i].size();j++){
        if (imgIntensite[i][j]<seuil)
                 out[i][j]=255;
  else{
      if((i>0 && imgContour[i-1][j]==0)||(i<imgIntensite.size()-1 && imgContour[i+1][j]==0)|| (j>0 && imgContour[i][j-1]==0)||(j<imgContour[0].size()-1 && imgContour[i][j+1]==0)||(imgContour[i][j]==0))
          out[i][j]=0;
  }

    }
    }
        return out;
}

/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
  ImageGris imgContour = seuillage(imgIntensite, seuilFort);

    // propager le contour avec le seuilFaible nbAmeliorations fois
    for (int i = 0; i < nbAmeliorations; i++) {
        imgContour = doubleSeuillage(imgIntensite, imgContour, seuilFaible);
    }

    return imgContour;
    
}





    


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )),50 ), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;


 

}

void doubleSeuillageTest(){
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
        ImageGris( {
            {255, 255, 255, 255},
            {255, 0, 0, 255},
            {255, 255, 0, 255},
            {255, 255, 255, 255}
        }),
        0.001) );

    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 80), 50), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
}


int main(){
   renormaliseTest();

    // Tester seuillage
    seuillageTest();

    // Tester double seuillage
    doubleSeuillageTest();

    // Tester double seuillage iteratif
    doubleSeuillageIteratifTest();

    cout << "Tous les tests terminés." << endl;

    return 0;


  
}

