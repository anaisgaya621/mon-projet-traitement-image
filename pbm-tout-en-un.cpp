#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include<iomanip>

using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
   ifstream PBM;
    ImageNB img;
    
PBM.open(source);
if (not PBM)
    throw runtime_error("Fichier non trouve: "+source);
    string type;
    int k;
    int width;
    int height;
    PBM>>type;
    PBM>>width;
    PBM>>height;
    img.resize(height);
   for (int i=0;i<height;i++){
       for(int j=0;j<width;j++){
          if (!(PBM >> k))
                throw runtime_error("Pixels manquants");
        if(k!=0 && k!=1)
      throw runtime_error("Fichier non trouve: "+source);
         img[i].push_back(k);
       
   }
   }
    PBM.close();
    return img;
}

/// BEGIN ecrirePBM

/** Ecrit une image naire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream flux;
    flux.open(cible);
    flux<<"P1"<<endl;
        flux<<img[0].size()<<" "<<img.size()<<endl;
       for(int i=0;i<img.size();i++){
           for (int j=0;j<img[i].size();j++){
               flux<<setw(2)<<img[i][j];
               
           }
           flux<<endl;
           
       }
    flux.close();
    
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            cout<<img[i][j];
        }
        cout<<endl;
    }
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
     for(int i=0;i<img.size();i++){
        for(int j=0;j<img[i].size();j++){
            if(img[i][j]==0)
            img[i][j]=1;
            else 
            img[i][j]=0;
                
            
        }
}
    return img;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

int main(){
    testLirePBM();

 

    return 0;
}


