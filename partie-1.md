---
jupytext:
  notebook_metadata_filter: exports, myst
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

+++ {"deletable": false, "editable": false, "grade_id": "cell-0c3482289ed8e634"}

# Partie 1 : Commençons avec les images noir et blanc

+++ {"deletable": false, "editable": false, "grade_id": "cell-a1bd30aeaa84edf4"}

## Le format PBM non compressé 

Dans la première partie de ce projet, on se contentera de lire et
d'écrire des images en noir et blanc au format `PBM` non
compressé.

+++ {"deletable": false, "editable": false, "grade_id": "cell-aef06ca3a83a5024"}

Description du format PBM
-------------------------

La page <http://fr.wikipedia.org/wiki/Portable_pixmap> détaille le
format général d'un fichier PBM. L'entête est de la
forme:

    P1
    nbColonne nbLigne
    
(par exemple `512 512`) suivi d'une liste de 0 ou de 1, séparés par des espaces ou des sauts de lignes, décrivant les pixels de haut en bas et de gauche à droite

(**Attention:** les lignes de l'image ne sont pas forcément les
mêmes que celles du fichier!).

Prenez le temps d'ouvrir (comme fichier texte et comme image) les fichiers PBM qui sont fournis dans le projet (cf [Visualisation des images PBM PGM et PPM](partie-0.md) )

En principe, les spécifications du format de fichier PBM indiquent de
plus qu'aucune ligne du fichier ne doit dépasser 70 caractères;
cependant la plupart des logiciels s'en sortent même si cette
contrainte n'est pas respectée. Les spécifications indiquent aussi
qu'un fichier PBM peut contenir des commentaires, sous la forme de
ligne commençant par un '\#'.

+++

## Premiers programmes

+++ {"deletable": false, "editable": false, "grade_id": "cell-09dc2666b3643f75"}

::::{admonition} Exercice 1.1 (\*) : Affichage d'une image PBM 

Le premier exercice de ce projet consiste à afficher une image PBM dans
le terminal: les pixels blancs seront des espaces et les pixels noirs
des symboles "@".

Par exemple:

    0 1 1 0                            @ @
    1 0 0 1    s'affichera          @       @
    1 0 0 1                         @       @
    0 1 1 0                            @ @

Dans le fichier [pbm-affiche.cpp](pbm-affiche.cpp), implantez la fonction `affichePBM` dont la documentation vous est fournie. Puis
compilez et vérifiez que votre programme affiche correctement l'image smiley.
::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-8cdd5b1c540b1676"}

::::{admonition} Exercice 1.2 (\*) :  Inverser le blanc et le noir 


Complétez la fonction `inversePBM` du fichier [pbm-affiche.cpp](pbm-affiche.cpp). 
Cette fois, il ne faut pas afficher mais **créer** un nouveau fichier PBM (avec le bon format !) pour fabriquer une nouvelle image en inversant le noir et le blanc.

Compilez et vérifiez que l'exécution donne le résultat attendu.

::::

**Comment visualiser l'image crée ? Voir les explications dans le [préambule](partie-0.md)**

+++ {"deletable": false, "editable": false, "grade_id": "cell-25a704be6307b600"}

## Lecture et Ecriture avec un tableau

Dans ce projet, on va effectuer de nombreux traitements d'images. Parfois,
il sera utile de charger l'image dans un tableau pour effectuer ces traitements.
En particulier, cela permet de séparer et d'implanter une fois pour toutes
tout ce qui concerne la lecture et l'écriture des fichiers.

Pour cela, on définit le type suivant :

    typedef vector<vector<int> > ImageNB;

Une image numérique en noir et blanc est donc représentée par un double tableau
contenant des entiers (0 ou 1). Par convention, le pixel (0,0) (auquel on accède dans l'image
`img` par `img[0][0]`) est le coin en haut à
gauche de l'image. Le premier indice désigne les lignes et le deuxième
les colonnes. Par exemple, le pixel (2,10) correspondant à
`img[2][10]` est le pixel de la troisième ligne et de la
onzième colonne (si l'image est suffisamment grande pour contenir ce
pixel bien entendu).

+++ {"deletable": false, "editable": false, "grade_id": "cell-53594d968bbcc5d0"}

::::{admonition} Exercice 1.3 (\*) Lecture d'une image PBM 

Implantez la fonction `lirePBM` du fichier [pbm-tout-en-un.cpp](pbm-tout-en-un.cpp)

Indication: utilisez les instructions suivantes pour ouvrir un
fichier et émettre un message d'erreur si celui-ci n'existe pas:

    ifstream PBM;
    PBM.open(source);
    if (not PBM)
        throw runtime_error("Fichier non trouve: "+source);

*Optionnel:* gérer les fichiers contenant des commentaires; si vous ne
le faites pas, il vous faudra vérifier que les fichiers PBM que vous
utilisez sont effectivement sans commentaires et les supprimer le cas
échéant.

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-b52eb7fefa798b34"}

::::{admonition} Exercice 1.4 (\*) : Écriture d'une image PBM 


Implantez la fonction `ecrirePBM` du fichier [pbm-tout-en-un.cpp](pbm-tout-en-un.cpp)

Indications:

-   Pour l'écriture, il est acceptable de ne mettre qu'un pixel par
    ligne (c'est moins lisible pour l'humain mais plus facile à
    programmer et équivalent pour l'ordinateur).

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-f6b3af5ee8bda6b7"}

## Tests de lecture et d'écriture

Des tests sont fournis dans le fichier [pbm-tout-en-un.cpp](pbm-tout-en-un.cpp). Par
défaut, le programme lance ces tests. Compilez et exécutez le
programme  [pbm-tout-en-un.cpp](pbm-tout-en-un.cpp) et vérifiez que vos codes sont
corrects.

+++ {"deletable": false, "editable": false, "grade_id": "cell-6608d47fccbbaa41"}

## Affichage et Inversion


::::{admonition} Exercice 1.5 (\*) : 

Complétez à présent le fichier [pbm-tout-en-un.cpp](pbm-tout-en-un.cpp) avec de nouvelles versions de vos fonctions `affichePBM` et `inversePBM` en utilisant le type `imageNB`.

Modifiez la fonction `main` pour qu'elle affiche et inverse l'image du smiley en utilisant ces nouvelles fonctions.
::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-a72667ca6bb05535"}

## Compléter le rapport

+++ {"deletable": false, "editable": false, "grade_id": "cell-4098677e7c612460"}

Ouvrez le fichier [rapport.md](rapport.md) et complétez ce qui correspond à la Partie 1. En particulier, vérifier que l'exécution et les tests proposés fonctionnent.

**Bravo ! Avec ces premiers exercices, vous avez compris la base de la lecture / écriture d'images au format text** Vous pouvez passer à la [Partie 2](partie-2.md)

```{code-cell} ipython3
Le programme lit et écrit des images binaires PBM (P1) en matrice 2D (ImageNB).
lirePBM charge le fichier, ecrirePBM l’enregistre avec des espaces alignés.
```
