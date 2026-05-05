---
jupytext:
  notebook_metadata_filter: exports, myst
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

+++ {"deletable": false, "editable": false, "grade_id": "cell-023e4da63cee5c06"}

# Projet : Traitement d'Images Numériques

+++ {"deletable": false, "editable": false, "grade_id": "cell-02d5d98a6c1394bb"}

## Introduction 

L'objectif de ce projet est d'utiliser les compétences que vous avez acquises pour implanter des algorithmes de traitement d'images sur des images en format texte (PBM, PGM, et PPM)

::::{admonition} Exemple : détection de contours

:::{image} images/Willis_gris.png
:alt: Portrait de Bruce Willis en noir et blanc
:width: 30%
:::
:::{image} images/gradient.jpg
:alt: Les contours de l'image dessinés en blanc sur fond noir
:width: 30%
:::

::::


::::{admonition} Exemple : calcul de zones de couleur uniforme avec l'algorithme SuperPixel.

:::{image} images/Willis.512.jpg
:alt: Portrait de Bruce Willis en couleur
:width: 30%
:::
:::{image} images/superpixel.jpg
:alt: Portrait de Bruce Willis découpé en zones de couleur uniforme
:width: 30%
:::

::::

+++ {"deletable": false, "editable": false, "grade_id": "cell-870f8e29c17dd60c"}

C'est un projet **guidé**, découpé en exercices pensés de façon **progressive**. Ne vous fiez pas à sa longueur, il est volontairement long afin que chacun puisse
s'exprimer en fonction de ses compétences, de son éventuelle
expérience préalable et de ses goûts. À vous de choisir un
sous-ensemble adapté des questions.

Il a été conçu pour qu'un étudiant
sans expérience de programmation préalable mais ayant suivi le module
avec assiduité puisse facilement avoir au minimum 12.
D'autre part, l'expérience que vous accumulerez au cours des premières
questions vous fera paraître les questions ultérieures plus simples.
Et vous aurez un vrai sentiment d'accomplissement en progressant dans
le sujet.

Toutes les parties portent sur des techniques basiques de traitement d'images.
Mais bien évidemment, ce n'est qu'un prétexte pour vous faire
travailler les notions centrales du cours: tests, tableaux, boucles,
fonctions, compilation séparée. Aucune notion de traitement d'images
n'est prérequise.

+++ {"deletable": false, "editable": false, "grade_id": "cell-86060b85b4d4556a"}

Niveaux de difficultés du projet
--------------------------------

Les exercices sont classés en fonction de leur difficulté :

-   Question facile: (\*)

-   Question moyenne: (\*\*)

-   Question difficile: (\*\*\*)

Les sections *Aller plus loin* vous donnent des pistes pour aprofondir certains aspects. Elles ne sont pas nécessaires pour valider le projet mais sont prises en compte dans l'évaluation

+++ {"deletable": false, "editable": false, "grade_id": "cell-7d11d871ce6b615b"}

Les différentes parties du projet
---------------------------------

Le projet commence par un [préambule](partie-0.md) qui rappelle les bases des formats images PBM PGM et PPM et vous sert d'outil de visualisation. Puis il est découpé en exercices selon six parties:

* [Partie 0](partie-0.md) : préambule, conversion et visualisation des images
* [Partie 1](partie-1.md) : traitements basiques d'images binaires
* [Partie 2](partie-2.md) : traitements basiques d'images en niveaux de gris
* [Partie 3](partie-3.md) : extraction de contours
* [Partie 4](partie-4.md) : mise en place d'une bibliothèque de traitement d'images
* [Partie 5](partie-5.md) : Traitements d'images en couleurs
* [Partie 6](partie-6.md) : Segmentation en régions par la méthode du super pixel

**Remarque:** les premiers exercices sont faits dans des fichiers indépendants. Puis, à la fin du projet,
on passe à une organisation multi-fichiers dans le but de créer une bibliothèque
de traitement d'images.

Les exercices de la partie 1 sont pensés de façon
progressive pour introduire les notions de base dont
nous aurons besoin dans le projet.

Les fonctions de **la partie 2**
sont indispensables pour la suite du projet. L'objectif est d'arriver
à implanter **la partie 3** (qui dépend de 2)
et **la partie 6** (qui dépend de 2, 4 et 5).

À l'intérieur d'une partie, les questions se
suivent (sauf exceptions indiquées). En dehors de ces dépendances, vous pouvez travailler sur
ce projet dans l'ordre que vous souhaitez.

Par ailleurs, nous vous fournissons aussi

-   Une proposition de squelette des fichiers, avec de la
    documentation et des tests;

-   Des exemples d'images et des résultats de traitements par les
    différents filtres pour comparer avec les vôtres.

+++ {"deletable": false, "editable": false, "grade_id": "cell-4b211d372d6cb2dc"}

Comment tester vos fonctions et programmes
------------------------------------------

Lors des premiers exercices, vous trouverez des tests directement dans les fichiers
à remplir. A partir de la partie 4, des fichiers spécifiques de test sont proposés pour chaque module. A vous de **compléter** et **ajouter** les tests nécessaires.

Pensez à remplir le [rapport.md](rapport.md) au fur et à mesure.

```{code-cell}

```
