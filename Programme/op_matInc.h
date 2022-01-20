#ifndef __op_matInc_h
#define __op_matInc_h

#include "creer_graphe.h"

/**
 * @brief Structure sur un chemin simple dans le graphe résiduel.
 * @struct Chemin op_matInc.h
 */
typedef struct{
    int nbSommet;
    TElement sommets[6];
    TElement ligneSansSom[6];
}Chemin;

Chemin chemin;


/**
 * @brief Vérifie si il y a encore un chemin dans le graphe résiduel de flot et l'indique 
 * dans la structure Chemin.
 * 
 * @param e entrée du graphe
 * @param col colonne du tableau des arcs
 * @param s sortie du graphe
 * @param gRes graphe résiduel
 * @param index du sommet à rentrer pour faire le chemin
 * @return int 1 s'il existe un chemin simple de e vers s, 0 sinon
 */
int cheminSimpleExiste(TElement e, TElement s, MatIncidence *flot, int index);

/**
 * @brief Supprime l'arc sans le chemin simple de l'entrée vers la sortie. 
 * 
 * @param s sommet sans successeur
 * @param flot graphe résiduel
 * @return int sommet prédecesseur dans l'arc supprimé
 */
int suppArcSansChemin(TElement s, MatIncidence *flot);

/**
 * @brief Vérifie si la ligne de la matrice contient au moins un arc, plus explicitement, si elle 
 * n'a pas de valeur différence de 0 pour toute la ligne alors le sommet est inutilisable pour 
 * trouver un chemin dans le graphe résiduel.
 * 
 * @param ligne de la matrice
 * @param flot matrice d'incidences du graphe résiduel
 */
void estLigneSansSommet(TElement ligne, MatIncidence *flot);

/**
 * @brief Trouve le chemin avec le flot minimum entre les différents arcs du chemin
 * 
 * @param flot représentant le graphe résiduel
 * @param matInc représentant le graphe à traiter
 * @param e sommet de départ
 * @return int le flot minimal trouvé
 */
int minChemin(MatIncidence *flot, MatIncidence matInc, TElement e);

/**
 * @brief Trouve la ligne du successeur pour une colonne donnée.
 * 
 * @param col 
 * @param flot 
 * @return int numéro de la ligne dans la matrice d'incidences
 */
int trouveSucc(TElement col, MatIncidence *flot);

/**
 * @brief Trouve la colonne correspondant à un arc du graphe.
 * 
 * @param s sommet de départ
 * @param succ sommet extrémité
 * @param mInc matrice d'incidence
 * @return int le numéro de la colonne pour l'arc donnée
 */
int trouverColonne(TElement s, TElement succ, MatIncidence mInc);

/**
 * @brief Ajoute le nouveau flot à l'arc résiduel.
 * 
 * @param s sommet de départ
 * @param succ successeur
 * @param flot graphe résiduel
 * @param flotMin flot de l'arc donné en paramètre
 */
void construireGrapheRes(TElement s, MatIncidence *flot, TCout flotMin, MatIncidence mInc);

/**
 * @brief Supprime un arc du graphe résiduel si celui-ci est utilisé dans un flot construit.
 * 
 * @param s sommet de départ
 * @param t extrémité
 * @param flot graphe résiduel
 */
void suppArcGrapheRes(TElement s, TElement t, MatIncidence *flot);

/**
 * @brief Affiche le graphe résiduek de notre graphe.
 * 
 * @param flot graphe résiduel
 */
void affichageGrapheRes(MatIncidence *flot);

#endif