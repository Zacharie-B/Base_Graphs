#ifndef __allocation_h
#define __allocation_h

#include <stdio.h>
#include <stdlib.h>

typedef int TElement;
typedef int TCout;

/**
 * @brief Structure de la matrice d'adjacence.
 * @struct MatAdjacence allocation.h
 */
typedef struct{
    int nbSom;
    TElement **mat;
    TCout **cout;
}MatAdjacence;

/**
 * @brief Structure de la matrice d'incidence.
 * @struct MatIncidence allocation.h
 */
typedef struct{
    int nbSom;
    int nbArcs;
    TElement **mat;
    TCout **cout;
}MatIncidence;

// Gestion de la mémoire des éléments basiques des graphes.
TElement *allocTabF(int n);
TCout *allocTabCout(int n);
void libMemTab(TElement **tab);
void libMemTabC(TCout **cout);

// Gestion de la mémoire des représentations du graphe sous forme de matrice.
TElement **allocMatF(int n, int m);
TCout **allocCoutF(int n, int m);
void libMemMatP(int nblig, TElement ***mat, TCout ***cout);

MatAdjacence allocMatAdjF(int nMax);
MatIncidence allocMatIncF(int n, int p);
void libMatAdj(MatAdjacence *mAdj);
void libMatInc(MatIncidence *mInc);


/**
 * @brief Structure de la file des successeurs.
 * @struct FileSucc allocation.h
 */
typedef struct{ 
    int nbSom;
    int nbArcs;
    TElement *FS; // tableau des successeurs indicés par arc
    int *APS; // tableau des arcs(successeurs) indicés par sommet
    TCout *Cout; // tableau des coûts d'un arc indicés par arc
}FileSucc;

// Gestion de la mémoire des representations du graphe sous forme de file des successeurs.
FileSucc allocFileSucc(int nbSommets, int nbArcs);
void libFileSucc(FileSucc *fs);


/**
 * @brief Structure de liste chainée de(s) successeur(s) pour un sommet.
 * @struct Liste allocation.h
 */
typedef struct cellule{
    TElement somSucc; // sommet successeur de l'indice du tableau
    TCout cout; // coût de l'arc
    struct cellule *suiv; // adresse de la prochaine cellule = adresse du prochain
                          // successeur pour un même sommet
}*Liste;

/**
 * @brief Structure de la liste d'adjacence avec un tableau de la liste des successeurs.
 * @struct ListAdjacence allocation.h
 */
typedef struct{
    int nbSom; // nombre de sommets du graphe
    Liste *tabAdj; // tableau des sommets des successeurs pour chaque sommet (indice du tableau)
    }ListAdjacence;

// Gestion de la mémoire de la liste d'adjacence.
Liste creatCellule();
ListAdjacence allocListAdjacence(int nbSom);

// Gestion de la mémoire de tableau à 2 dimensions.
int *allocTabInt(int n);
void libMemTabInt(int **tab);
int **allocMatrice(int n);
void libMemMatrice(int ***mat, int nblig);

#endif