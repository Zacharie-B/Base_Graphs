#ifndef __op_matrice_h
#define __op_matrice_h

#include <limits.h>
#include "creer_graphe.h"


/**
 * @brief Renvoie tous les successeurs d'un sommet du graphe
 * 
 * @param succs tableau avec les sommets successeurs du sommet de départ
 * @param mAdj matrice d'adjacence représentant le graphe
 * @param s sommet de départ
 * @return int nombre de successeurs tableau des sommets successeurs du sommet de départ
 */
int successeurs(TElement** succs, MatAdjacence mAdj, int s);

/**
 * @brief Recherche et trouve le chemin direct avec le cout minimum.
 * 
 * @param mAdj matrice d'adjacence représentant le graphe
 * @param s sommet de départ
 * @return TElement sommet avec le cout le plus faible
 */
TElement coutMin(MatAdjacence mAdj, TElement s, int *sommets);

/**
 * @brief Renvoie tous les successeurs d'un sommet du graphe, ils ne doivent pas 
 * être déjà explorés.
 * 
 * @param succs tableau avec les sommets successeurs du sommet de départ
 * @param mAdj matrice d'adjacence représentant le graphe
 * @param s sommet de départ
 * @param sommets ensemble de sommets explorés ou non
 * @return int nombre de successeurs tableau des sommets successeurs du sommet de départ
 */
int successeursDijsktra(TElement **succs, MatAdjacence mAdj, int s, int *sommets);

/**
 * @brief Renvoie le sommet suivant si l'on connait tous ces prédécesseurs.
 * 
 * @param sommets ensemble des sommets explorés ou non
 * @param mAdj matrice d'adjacence représentant le graphe
 * @param x pointeur sur le nombre de prédécesseur d'un sommet
 * @return int sommet à traiter en cas de succés, -1 en cas d'échec
 */
int choisirSommetsuivant(TElement **predecesseurs, int *sommets, MatAdjacence mAdj, int *x);

/**
 * @brief vérifie s'il y a un arc entre les sommets s et t
 * 
 * @param s sommet de départ
 * @param t sommet d'arrivé
 * @return int 1 en cas de réussite, 0 en cas d'échec
 */
int arcExiste(TElement s, TElement t, FileSucc fs);

#endif