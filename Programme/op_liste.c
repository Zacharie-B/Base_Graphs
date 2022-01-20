#include <limits.h>
#include "op_liste.h"


ListeAretes initListeAretes(){
    ListeAretes lar = (ListeAretes)malloc(sizeof(struct arete));
    lar->s = -1;
    lar->t = -1;
    lar->suivant = NULL;
    lar->cout = INT_MAX;
    return lar;
}

Liste successeurs(TElement s, ListAdjacence lAdj){
    return lAdj.tabAdj[s];
}

ListeAretes dernierLArete(ListeAretes la){
    ListeAretes der = la;
    while(der->suivant != NULL){
        der = der->suivant;
    }
    return der;
}

ListeAretes ajouterArete(TElement s, TElement somSucc, TCout cout, ListeAretes arete){
    ListeAretes der = NULL;
    if(arete == NULL){
        arete = (ListeAretes)malloc(sizeof(struct arete));
        arete->s = s;
        arete->t = somSucc;
        arete->cout = cout;
        arete->suivant = NULL;
    }
    else{
        der = dernierLArete(arete);
        ListeAretes nouvArete = der->suivant;
        nouvArete = (ListeAretes)malloc(sizeof(struct arete));
        nouvArete->s = s;
        nouvArete->t = somSucc;
        nouvArete->cout = cout;
        nouvArete->suivant = NULL;
        der->suivant = nouvArete;
    }
    return arete;
}

ListeAretes minimum(ListeAretes lar){
    int minimum = INT_MAX;
    ListeAretes tmp = lar;
    while(lar != NULL){
        if(minimum > lar->cout){
            minimum = lar->cout;
            tmp = lar;
        }
        lar = lar->suivant;
    }
    return tmp;
}

ListeAretes supprimer(ListeAretes arcMin, ListeAretes lar){
    ListeAretes tmp = lar;
    while((tmp->suivant != arcMin) && (tmp != arcMin)){
        tmp = tmp->suivant;
    }
    ListeAretes tmp2 = arcMin->suivant;
    tmp->suivant = tmp2;
    free(arcMin);
    return lar;
}

int nonCyclique(ListAdjacence arbreRecouvrement, ListeAretes arcMinimum){
    TElement s = arcMinimum->s;
    TElement t = arcMinimum->t;
    
    Liste tmp;
    int visite[arbreRecouvrement.nbSom];
    parcoursProfondeur(visite, s, arbreRecouvrement);
        
    if(visite[s] == 1 && visite[t] == 1){
        puts("Erreur lol");
        return 0;
    }
    return 1;
}

void parcoursProfondeur(int *visite, int sd, ListAdjacence g){
    int n = g.nbSom;
    int s = sd;
    for(int i = 0; i < n; i++){
        visite[i] = 0;
    }
    if(!visite[s]){
        reParcoursProfondeur(s, visite, g);
    }
}

void reParcoursProfondeur(int s, int *visite, ListAdjacence g){
    visite[s] = 1;
    // printf("Sommet visité : %d\n", s);
    // printf("adresse du sommet : %p\n", g.tabAdj[s]);
    if(g.tabAdj[s] != NULL){
        if(!visite[g.tabAdj[s]->somSucc]){ // t ∈ Γ(s)
            // printf("Le sommet %d va en : %d\n", s, g.tabAdj[s]->somSucc);
            // On remplace le sommet de départ (s) par t qui est le successeur de s
            reParcoursProfondeur(g.tabAdj[s]->somSucc, visite, g);
        }
    }
}

void afficherAretes(ListeAretes aretes){
    if(aretes == NULL){
        puts("Fin de la liste des arêtes");
    }
    else{
        printf("L'arc de %d à %d coûte %d\n", aretes->s, aretes->t, aretes->cout);
        afficherAretes(aretes->suivant);
    }
}