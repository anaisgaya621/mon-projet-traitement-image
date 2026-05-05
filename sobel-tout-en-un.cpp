#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
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
           int val=((int)img[i][j]);
            if(val>255)val=255;
            if(val<0) val=0;
            flux<<val<<" ";
            
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

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
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


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
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


///ici on va faire lissage pour l image avant appliquer le filtre sobel
ImageGris lissage(ImageGris img){
    int hauteur=img.size();
    int largeur=img[0].size();
     ImageGris imgTemp=img;
    for(int y=0;y<hauteur-1;y++){
        for(int x=0;x<largeur-1;x++){
            double somme=0;
            int count=0;
            // ici pour parcourir les pixels voisins de chaque pixel
            for(int dy=-1;dy<=1;dy++){
                for(int dx=-1;dx<=1;dx++){
                    int ny = y + dy;  
                    int nx = x + dx;
                    
                    // verifier si il existe des pixels voisins de chaque pixel(surtout pour les pixels de bordure)
                    if (ny >= 0 && ny < hauteur && nx >= 0 && nx < largeur) {
                 // imgTemp[y][x]=(img[y-1][x]+img[y+1][x]+img[y][x+1]+img[y][x-1]+img[y-1][x-1]+img[y+1][x+1]+img[y-1][x+1]+img[y+1][x-1])/8
                        somme += img[ny][nx];
                        count++;
                    }
                }
            }
             imgTemp[y][x] = somme / count;
                }
                
            }
       
           
        
    
    return imgTemp;
}


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
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


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

