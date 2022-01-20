#ifndef __arbre_recouvrement
#define __arbre_recouvrement

#include "op_liste.h"

/**
 * @brief Algorithme de kruskal qui trouve un arbre de recouvrement de poids minimum.
 * 
 * @param lAdj représente le graphe à analyser
 * @return ListAdjacence pour faire l'arbre de recouvrement de poids minimum.
 */
ListAdjacence kruskal(ListAdjacence lAdj);


#endif