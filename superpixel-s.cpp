#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"

double distancePoints(Point p, Point c) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction distancePoints non implantée ligne 10");
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction distanceAEnsemble non implantée ligne 15");
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction plusProcheVoisin non implantée ligne 20");
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction sousEnsemble non implantée ligne 25");
}

Point barycentre(EnsemblePoints Q) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction barycentre non implantée ligne 30");
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction KMoyenne non implantée ligne 35");
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implantée ligne 74");
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implantée ligne 79");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implantée ligne 84");
}



// Ecrire votre code ici


