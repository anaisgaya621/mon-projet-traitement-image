#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
  ifstream flux;
    flux.open(source);
    int k;
    int counter =0;
    string name;
    int width;
    int height;
    flux>> name;
    flux>>width;
    flux>>height;
    while(flux>>k ){
        if(k==0)
            cout<<" ";
     if(k==1)
            cout<<"@";
        counter ++;
         if (counter  == width) {
            cout << endl;
            counter = 0;
        }
    }
    flux.close();
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream out;
    ofstream in;
    string type;
    int k;
    int counter = 0;
    int width;
    int height;

    out.open(source);
    in.open(cible);

    out >> type;
    out >> width;
    out >> height;

    in << type << endl;
    in << width << " " << height << endl;

    while (out >> k) {
        // inversion
        if (k == 0)
            in << 1;
        else if (k == 1)
            in << 0;

        counter++;

        if (counter == width) {
            in << endl;
            counter = 0;
        } else {
            in << " ";     
        }
    }

    out.close();
    in.close();
}



int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

