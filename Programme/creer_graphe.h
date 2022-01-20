#ifndef __creer_graphe_h
#define __creer_graphe_h

#include "allocation.h"

/**
 * @brief Permet de lire un fichier contenant les données pour créer la file des successeurs.
 * 
 * @param nomFich chemin du fichier à lire
 * @return FileSucc file des successeurs crée
 */
FileSucc chargFileSucc(char *nomFich);

/**
 * @brief Initialise la file des successeurs avec une valeur (en général 0).
 * 
 */
void initFileSucc(int nbSommets, int nbArcs, int *APS, TElement *FS, TCout *cout, int valeur);

/**
 * @brief Affiche la file des successeurs du graphe.
 * 
 * @param fs file des successeurs du graphe
 */
void affichageFileSucc(FileSucc fs);

/**
 * @brief Renvoie le nombre de sommets d'un graphe
 * 
 * @param g graphe avec des sommets
 * @return int nombre de sommets du graphe
 */
int nbSom(MatAdjacence g);

/**
 * @brief Initialise une matrice avec une valeur (en général 0).
 * 
 */
void initMat(int x, int y, TElement **mat, TCout **cout, int valeur);

/**
 * @brief Permet de lire le fichier contenant les données pour créer la matrice d'adjacence.
 * 
 * @param nomFich chemin du fichier à lire
 * @return MatAdjacence matrice d'adjacence crée
 */
MatAdjacence chargMatAdj(char *nomFich);

/**
 * @brief Affiche le graphe sous la forme de matrice d'adjacence, avec le cout de chaque arc.
 * 
 * @param mAdj matrice d'adjacence du graphe
 */
void affichageMatAdj(MatAdjacence mAdj);

/**
 * @brief Renvoi l'adresse de la dernière cellule de la liste.
 * 
 * @param l liste des successeurs d'un sommet
 * @return Liste adresse du premier élément de la liste
 */
Liste dernier(Liste l);

/**
 * @brief Insert un nouveau successeur à la fin de la liste des successeurs
 *  d'un sommet.
 * On retourne l'adresse de la liste car la variable est local à la fonction vu que 
 * l'on agit sur une structure non pointé.
 * 
 * @param l liste des successeurs d'un sommet
 * @param somSucc numéro du sommet successeur
 * @param cout de l'arête vers ce successeur
 * @return Liste adresse du élément de la liste
 */
Liste inserQueue(Liste l, TElement somSucc, TCout cout);

/**
 * @brief Charge le graphe d'un fichier sous la forme d'une liste d'adjacences.
 * 
 * @param nomFichier à ouvrir pour construire la liste d'adjacence
 * @return ListAdjacence représentant le graphe construit
 */
ListAdjacence chargeListAdjacence(char *nomFichier);

/**
 * @brief Affiche la liste d'adjacence avec tous les successeurs qu'elle contient.
 * 
 * @param ladj à afficher sur la console.
 */
void afficheListeAdjacences(ListAdjacence ladj);

/**
 * @brief Affiche les successeurs d'un sommet.
 * 
 * @param l liste des successeurs du sommet
 * @param sommet numéro du sommet
 */
void afficheListeSucc(Liste l, int sommet);

/**
 * @brief Charge la matrice d'incidence d'un graphe à partir d'un fichier.
 * 
 * @param nomFichier à ouvrir poru construire le graphe
 * @return MatIncidence représentant le graphe construit
 */
MatIncidence chargMatInc(char *nomFichier);

/**
 * @brief Affiche l'ensemble de la matrice d'incidence.
 * 
 * @param matInc à afficher sur la console
 */
void affichageMatIncidences(MatIncidence matInc);

#endif