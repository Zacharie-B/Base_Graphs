#ifndef __op_liste_h
#define __op_liste_h

#include "creer_graphe.h"

/**
 * @brief Liste des arêtes du graphe avec leur coût.
 * @struct ListeAretes op_liste.h
 */
typedef struct arete{
    TElement s; // point A
    TElement t; // point B
    TCout cout; // coût de l'arête
    struct arete *suivant; // adresse de l'arete suivant
}*ListeAretes;

/**
 * @brief On initialise la liste d'arête avec une arête symbolique pour évitez les problèmes
 * lors de la suppression des arêtes avec le coût minimum.
 * 
 * @return ListeAretes liste la 1ère arête symbolique
 */
ListeAretes initListeAretes();
Liste successeurs(TElement s, ListAdjacence lAdj);
ListeAretes dernierLArete(ListeAretes la);

/**
 * @brief Ajoute chaque arête du graphe à la liste des arêtes.
 * 
 * @param s sommet A
 * @param somSucc sommet B
 * @param cout de l'arête
 * @param aretes liste de toutes les arêtes
 * @return ListeAretes liste de toutes les arêtes
 */
ListeAretes ajouterArete(TElement s, TElement somSucc, TCout cout, ListeAretes arete);

/**
 * @brief On cherche l'arc avec le coût minimum.
 * 
 * @param lar liste des arêtes pour créer l'arbre
 * @return ListeAretes adresse de l'arête avec le coût minimum
 */
ListeAretes minimum(ListeAretes lar);

/**
 * @brief Supprime une arête de la liste des arêtes. 
 * 
 * @param lar liste des arêtes pour créer l'arbre
 * @return ListeAretes adresse de l'arête avec le coût minimum
 */
ListeAretes supprimer(ListeAretes arcMin, ListeAretes lar);

/**
 * @brief Vérifie si l'arc minimum à ajouter ne forme pas de cycle.
 * 
 * @param arbreRecouvrement 
 * @param arcMinimum à ajouter à l'arbre de recouvrement
 * @return 1 si il n'y a pas de cycle, 0 si il forme un cycle
 */
int nonCyclique(ListAdjacence arbreRecouvrement, ListeAretes arcMinimum);

/**
 * @brief Prépare la recherche d'un chemin entre le sommet sd et t.
 * 
 * @param visite indique quels sommets sont visités durant son parcours
 * @param sd sommet de départ
 * @param g arbre de recouvrement
 */
void parcoursProfondeur(int *visite, int sd, ListAdjacence g);

/**
 * @brief Parcours tous les sommets accessibles depuis s, et indique quels sommets 
 * il a visité.
 * 
 * @param s sommet de départ
 * @param visite tableau du visiteur de sommet
 * @param g arbre de recouvrement
 */
void reParcoursProfondeur(int s, int *visite, ListAdjacence g);

void afficherAretes(ListeAretes aretes);

#endif