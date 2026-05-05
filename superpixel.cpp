#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"
#include<vector>


/// BEGIN distancePoints

/** Renvoie la distance Euclidienne entre deux points
 * @param p un point
 * @param c un point
 * @return la distance entre p et c
 **/
double distancePoints(Point p, Point c) {
   //on a p et c deux vecteur sooo
    double somme =0.0;
    for(int i=0;i<p.size();i++){
    somme=somme+pow(p[i]-c[i],2);
} 
    return sqrt(somme);}
    
/** Renvoie la distance Euclidienne d'un point a un ensemble de points
 * @param p un point
 * @param C un ensemble de points
 * @return la distance
 **/

double distanceAEnsemble(Point p, EnsemblePoints C) {
 //va remvoyer la distance la plus petite
  
     double distance_min=distancePoints(p, C[0]);
    for(int k=1;k<C.size();k++){
       double  dist=distancePoints( p, C[k]);
        if(dist<distance_min){
        distance_min=dist;
    
}
    }
    return distance_min;
}
/// BEGIN plusProcheVoisin

/** Renvoie le plus proche voisin d'un point p dans un ensemble C
 * @param p un point
 * @param C un ensemble de points
 * @return l'index du plus proche voisin c a dire Elle renvoie l’indice du point de C le plus proche de p.
 **/
int plusProcheVoisin(Point p, EnsemblePoints C) {
    int index_min = 0;
    double distancemin = distancePoints(p, C[0]);

    for(int j = 1; j < C.size(); j++){
        double dist = distancePoints(p, C[j]);
        if(dist < distancemin){
            index_min = j;
            distancemin = dist;
        }
    }
    return index_min;
}


/// BEGIN sousEnsemble

/** Renvoie les points p de P tels que C[k] est le plus proche voisin de p dans C
 * @param P un ensemble de points
 * @param C un ensemble de points
 * @param k un entier
 * @return un sous ensemble des points de P
 **/

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
EnsemblePoints result;
    for(int i=0;i<P.size();i++){
        if(plusProcheVoisin(P[i],C)==k)
            result.push_back(P[i]);
        
    }
    return result;
}
/// BEGIN barycentre

/** Renvoie le barycentre d'un ensemble de points
 * @param Q un ensemble de points
 * @return c le barycentre de Q
 **/
Point barycentre (EnsemblePoints Q) {
    if(Q.empty())
        throw runtime_error("ensemble est vide");
    Point C(Q[0].size(), 0.0);
    
    for(int j = 0; j < (int)Q[0].size(); j++) {
        for(int k = 0; k < (int)Q.size(); k++) {
            C[j] += Q[k][j];
        }
        C[j] /= Q.size();
    }
    return C;
}

/// BEGIN kMoyenne

/** Renvoie la K-moyenne de deux ensembles de points
 * @param P un ensemble de points 
 * @param C un ensemble de points
 * @param nbAmeliorations:entier le nombre de fois ou l'amelioration va etre effectuee
 * @return C un ensemble de points les positions finales de points pilotes
 **/
    //enft on a un ensemble de points P (pixels)
// on a un ensemble de centres C (les pilotes)
    //et dans chaqque point p on cherche un pilot c dans C
    //si on par eexemple 5 centre dans l enseble de point C alors on va obtenir 5 groupe ,c a d dasn chaque iteration of va construire un groupe qui va avoir le size de C
EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
      if(P.empty() || C.empty())
        throw runtime_error("Ensemble des points est vide");
    
    int size=C.size();
    for(int iter = 0; iter < nbAmeliorations; iter++) {
    vector<vector<Point>> groupes(size);//reinstaliser les grps chaque iteration pour qu il stabilise
    for(int i=0;i<P.size();i++){
       groupes[plusProcheVoisin( P[i], C)].push_back(P[i]);
    }
    for(int k = 0; k < size; k++) {
            if(!groupes[k].empty())
                C[k] = barycentre(groupes[k]);
        }}
    return C;
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
    
/// BEGIN pivotSuperPixel

/** Renvoie un ensemble de points (espace spatio colorimetrique)
 *  regulierement espaces dans une image
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @return un ensemble de points dans l'espace spatio colorimetrique ent cet espace est un modèle qui permet de représenter les couleurs par des valeurs numériques.
 **/

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints C;
    int hauteur = img.size();
    int largeur = img[0].size();
    for (int i = 0; i < hauteur; i += mu){
       for (int j = 0; j < largeur; j += mu){
           Point p;
           p.push_back(i);
           p.push_back(j);
           p.push_back(lambda * img[i][j].r);
           p.push_back(lambda * img[i][j].g);
           p.push_back(lambda * img[i][j].b);
           C.push_back(p);
       }
    }
    return C;
}

    
    
/// BEGIN superPixels

/** Renvoie les superpixels d'une image dans l'espace spatio colorimetrique
 * @param img une image en teintes de gris
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations un entier
 * @return un ensemble de points, les superpixels
 **/

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {

    EnsemblePoints C = pivotSuperPixel(img, lambda, mu);

  /*  EnsemblePoints P;
    int H = img.size();
    int W = img[0].size();

    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            Point p;
            p.push_back(i);
            p.push_back(j);
            p.push_back(lambda * img[i][j].r);
            p.push_back(lambda * img[i][j].g);
            p.push_back(lambda * img[i][j].b);
            P.push_back(p);
        }
    }*/
    EnsemblePoints P=pivotSuperPixel(img, lambda, 1);

    return FAST_KMoyenne(P, C, nbAmeliorations);
}


/// BEGIN SuperPixel

/** Filtre SuperPixel
 * @param img une image
 * @param lambda un double
 * @param mu un entier
 * @param nbAmeliorations
 * @return l'image associee aux superpixels d'une image
 **/
Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
  EnsemblePoints C= superPixels(img,lambda,mu,nbAmeliorations);
    int hauteur = img.size();
    int largeur = img[0].size();
    Image imgResult = img;
    vector<vector<int>> labels(hauteur, vector<int>(largeur));// qui contien les indice des pivots

    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            Point p={(double)i,(double)j,(double)img[i][j].r,(double)img[i][j].g,(double)img[i][j].b};//on construit le point qui correspond a chaque pixel de l image
           int k= plusProcheVoisin(p,C);//renvoie l indice du pivot qui correspond au point associe au pixel de l image
            imgResult[i][j].r=C[k][2]/lambda;// le k c est l indice du pivot et 2 c est l indice de la couleur rouge[ c[k]=(x,y,r,g,b)
            imgResult[i][j].g=C[k][3]/lambda;//meme chose
            imgResult[i][j].b=C[k][4]/lambda;
            
        }
    }

    //ici on ajoute la zone blue  a la frontiere de chaque super pixel
    
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            Point L = {(double)i,(double)j,
                   (double)img[i][j].r,
                   (double)img[i][j].g,
                   (double)img[i][j].b};
        labels[i][j] = plusProcheVoisin(L, C); // chaque indice du point du pixel est  associe a lindice du pivot
        }
    }

    for(int i=0;i<hauteur;i++)
    for(int j=0;j<largeur;j++) {
        bool estFrontiere = false;
        int k = labels[i][j];
        if(i>0 && labels[i-1][j]!=k) estFrontiere = true;
        if(i<hauteur-1 && labels[i+1][j]!=k) estFrontiere = true;
        if(j>0 && labels[i][j-1]!=k) estFrontiere = true;
        if(j<largeur-1 && labels[i][j+1]!=k) estFrontiere = true;

        if(estFrontiere) {
            imgResult[i][j].r = 0;
            imgResult[i][j].g = 0;
            imgResult[i][j].b = 255;
        }
    }

    return imgResult;
}




// Ecrire votre code ici


