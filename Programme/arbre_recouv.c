#include "arbre_recouv.h"

int main(){
    ListAdjacence lAdj = chargeListAdjacence("donnees_graphe/arbreRec.txt");
    kruskal(lAdj);
    
    return 0;
}


ListAdjacence kruskal(ListAdjacence lAdj){
    puts("\n############################################################");
    puts("Recherche de l'arbre de recouvrement");
    int nbSommets = lAdj.nbSom;
    ListAdjacence arbreRecouvrement = allocListAdjacence(nbSommets);
    ListeAretes aretes = initListeAretes();
    for(int s = 0; s < nbSommets; s++){
        Liste succs = successeurs(s, lAdj);
        
        while(succs != NULL){
            aretes = ajouterArete(s, succs->somSucc, succs->cout, aretes);
            succs = succs->suiv;
        }
        arbreRecouvrement.tabAdj[s] = NULL;
    }
    arbreRecouvrement.nbSom = nbSommets;
    int cpt = 1, coutTotal = 0;
    while(cpt < nbSommets){
        // afficherAretes(aretes);
        ListeAretes arcMinimum = minimum(aretes);
        printf("arc minimum de %d à %d coute : %d\n", arcMinimum->s, arcMinimum->t, arcMinimum->cout);
        if(nonCyclique(arbreRecouvrement, arcMinimum)){
            Liste l1 = arbreRecouvrement.tabAdj[arcMinimum->s];
            l1 = inserQueue(l1, arcMinimum->t, arcMinimum->cout);
            arbreRecouvrement.tabAdj[arcMinimum->s] = l1;
            
            coutTotal += arcMinimum->cout;
            cpt++;
        }
        aretes = supprimer(arcMinimum, aretes);
    }

    afficheListeAdjacences(arbreRecouvrement);
    
    printf("Le coût total de l'arbre est %d\n", coutTotal);
}
