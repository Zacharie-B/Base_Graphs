#include "op_matrice.h"

int successeurs(TElement **succs, MatAdjacence mAdj, int s){
    TElement n = nbSom(mAdj);
    int x = 0;
    for(TElement i = 0; i < n; i++){
        if(mAdj.mat[s][i] != 0){
            x++;
        }
    }
    x = 0;
    // Toujours utilisé une variable intermédiaire = à l'adresse du paramètre
    // sinon problème de pointeur qui va dans l'ESPACE
    TElement *successeur = *succs;
    for(TElement i = 0; i < n; i++){
        if(mAdj.mat[s][i] != 0){
            successeur[x] = i;
            x++;
        }
        
    }
    return x;
}

TElement coutMin(MatAdjacence mAdj, TElement s, int *sommets){
    TElement distMin = INT_MAX;
    TElement sommetDistMin;
    int n = nbSom(mAdj);
    for(int i = 0; i < n; i++){
        if(sommets[i] != 0){
            if((distMin >= mAdj.cout[s][i]) && (mAdj.mat[s][i])){
                distMin = mAdj.cout[s][i];
                sommetDistMin = i;
            }
        }
    }
    return sommetDistMin;
}

int successeursDijsktra(TElement **succs, MatAdjacence mAdj, int s, int *sommets){
    TElement n = nbSom(mAdj);
    int x = 0;
    for(TElement i = 0; i < n; i++){
        // si le i est un successeur de s et il n'est pas encore visité
        if((mAdj.mat[s][i]) && (sommets[i] != 0)){
            x++;
        }
    }
    x = 0;
    // Toujours utilisé une variable intermédiaire = à l'adresse du paramètre
    // sinon problème de pointeur qui va dans l'ESPACE
    TElement *successeur = *succs;
    for(TElement i = 0; i < n; i++){
        // si c'est un succcesseur de s et qu'il n'est pas encore visité
        if((mAdj.mat[s][i]) && (sommets[i] != 0)){
            successeur[x] = i;
            x++;
        }
    }
    return x;
}

int choisirSommetsuivant(TElement **predecesseurs, int *sommets, MatAdjacence mAdj, int *x){
    int n = nbSom(mAdj);
    int i;
    int *nbPred = x;
    TElement *preds = *predecesseurs;
    for(i = 0; i < n; i++){
        if(sommets[i] != 0){
            // On stocke tous les prédécesseurs de i
            for(int j = 0; j < n; j++){
                // printf("mAdj.mat[j][i] : %d\n", mAdj.mat[j][i]);
                if(mAdj.mat[j][i]){
                    preds[*nbPred] = j;
                    *nbPred = *nbPred + 1;
                    // printf("Le sommet %d est un prédécesseur de %d\n", j, i);
                }
            }
            int aTousPredecesseurs = 1;
            // On vérifie que chaque prédécesseur est exploité
            // printf("valeur du nombre de prédécesseur de %d est %d\n", i, *nbPred);
            for(int y = 0; y < *nbPred; y++){
                // printf("adresse du prédécesseur : %p\n", &preds[y]);
                if(sommets[preds[y]] != 0){
                    aTousPredecesseurs = 0;
                }
            }
            if(aTousPredecesseurs){
                // puts("On a trouvé un sommet avec tous ces prédécesseurs exploités");
                break;
            }
            *nbPred = 0;
        }
    }
    // printf("sommet max : %d\n",i);
    if(i == n){
        return -1;
    }
    return i;
}

int arcExiste(TElement s, TElement t, FileSucc fs){
    printf("sommet à atteindre : %d\n", t);
    int nbSucc = fs.APS[s + 1] - fs.APS[s];
    printf("nombre de successeur : %d\n", nbSucc);
    int numPremierArc = fs.APS[s];
    printf("numéor du premier arc : %d\n", numPremierArc);
    for(int i = 0; i < nbSucc; i++){
        printf("successeur de %d est : %d\n", numPremierArc + i, fs.FS[numPremierArc + i]);
        if(fs.FS[numPremierArc + i] == t)   return numPremierArc + i;
    }
    return -1;
}