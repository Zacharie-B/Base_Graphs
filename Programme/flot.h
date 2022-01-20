#ifndef __flot_h
#define __flot_h

#include "op_matInc.h"

/**
 * @brief Applique l'algorithme de ford_fulkerson qui permet de trouver 
 * le flot maximal dans un graphe.
 * 
 * @param e sommet sans prédécesseur => entrée du graphe
 * @param s sommet sans successeur => sortie du graphe
 * @param matInc représentant le graphe à traiter 
 * @return int flot maximal résultat du graphe
 */
int fordFulkerson(TElement e, TElement s, MatIncidence matInc);

/**
 * @brief Affiche le chemin pris par le flot
 * 
 * @param e 
 */
void affichageChemin(TElement e);

/**
 * @brief Ré-initialise le tableau de marqueage après avoir trouvé le chemin.
 * 
 * @param n
 * @param p
 */
void reInitMarquage(int n, int p);

#endif