#ifndef __PCC_h
#define __PCC_h

#include "op_matrice.h"

/**
 * @brief Algorithme de ford.
 * Trouve le chemin le plus court entre le sommet de départ et 
 * tous les autres sommets du graphe.
 * 
 * @param s sommet de départ
 * @param mAdj graphe représenté par une matrice d'adjacence
 * @param couts tableau du coût du chemin vers le sommet (indice du tableau)
 * @param pred sommet prédeccesseur du sommet (indice du tableau)
 */
void ford(int s, MatAdjacence mAdj, int *couts, int *pred);

/**
 * @brief Algorithme de dijsktra.
 * Trouve le chemin le plus court entre le sommet de départ et 
 * tous les autres sommets du graphe.
 * 
 * @param s sommet de départ
 * @param mAdj graphe représenté par une matrice d'adjacence
 * @param couts tableau du coût du chemin vers le sommet (indice du tableau)
 * @param pred sommet prédeccesseur du sommet (indice du tableau)
 */
void dijsktra(int s, MatAdjacence mAdj, int *couts, int *pred);

/**
 * @brief Algorithme de Bellman.
 * Trouve le chemin le plus court entre le sommet de départ et 
 * tous les autres sommets d'un graphe sans circuit.
 * 
 * @param s sommet de départ
 * @param mAdj graphe représenté par une matrice d'adjacence
 * @param couts tableau du coût du chemin vers le sommet (indice du tableau)
 * @param pred sommet prédeccesseur du sommet (indice du tableau)
 */
void bellman(int s, MatAdjacence mAdj, int *couts, int *pred);

/**
 * @brief Algorithme de Floyd.
 * Trouve le chemin le plus court entre chaque couple de sommets d'un graphe.
 * 
 * @param fs file des successeurs représentant le graphe
 * @param cout tableau à 2 dimmensions du graphe du cout des arcs
 * @param pred tableau à 2 dimmensions du graphe des prédécesseurs des arcs
 */
void floyd(FileSucc fs, int **cout, int **pred);

/**
 * @brief Affiche le cout et les prédécesseurs des sommets avec la file 
 * des successeurs du graphe.
 * 
 * @param fs file des successeurs
 * @param couts cout de chaque arc
 * @param preed prédécesseur de chaque sommet
 */
void affichageCoutPredFS(FileSucc fs, int **couts, int **pred);

#endif