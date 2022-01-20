#include "pcc1.h"

int main(int argc, char **argv){

    TCout *couts;
    TElement *pred;

    // puts("\n########################################################");
    // puts("\nGraphe traité par l'algorithme de ford");
    // MatAdjacence mAdjFord = chargMatAdj("donnees_graphe/test.txt");
    // ford(0, mAdjFord, couts, pred);

    puts("\n########################################################");
    puts("\nGraphe traité par l'algorithme de dijsktra");
    MatAdjacence mAdjDijsktra = chargMatAdj("donnees_graphe/dijsktra_graphe.txt");
    dijsktra(0, mAdjDijsktra, couts, pred);

    // puts("\n########################################################");
    // puts("\nGraphe traité par l'algorithme de bellman");
    // MatAdjacence mAdjBellman = chargMatAdj("donnees_graphe/bellman_graphe.txt");
    // bellman(0, mAdjBellman, couts, pred);

    // puts("\n########################################################");
    // puts("\nGraphe traité par l'algorithme de floyd");
    // FileSucc fs = chargFileSucc("donnees_graphe/floyd.txt");
    // floyd(fs, &couts, &pred);

    return 0;
}


void ford(int s, MatAdjacence mAdj, TCout *couts, TElement *pred){
    // Initialisation
    int n = nbSom(mAdj);
    // On initialise le coût du chemin de chaque sommet

    couts = allocTabCout(n);
    couts[s] = 0;
    for(int i = 0; i < n; i++){
        if(i != s)  couts[i] = INT_MAX;
    }
    // On initialise le prédeccesseur de chaque sommet
    pred = allocTabF(n);
    pred[s] = s;
    for(int i = 0; i < n; i++){
        if(i != s)  pred[i] = -1;
    }
    
    int modif = 1;
    while(modif){
        modif = 0;
        // Traitement des arcs dans l'ordre s1 -> sn
        for(int i = 0; i < n; i++){
            // Ce tableau est la liste des successeurs du sommet de départ (i)
            TElement *succs;
            succs = allocTabF(n);
            int nbSucc = successeurs(&succs, mAdj, i);
            // Pour chaque successeur de i on cherche à trouver son chemin le plus court
            for(int j = 0; j < nbSucc; j++){
                TCout valeur = couts[i] + mAdj.cout[i][succs[j]];
                if(valeur < couts[succs[j]]){
                    couts[succs[j]] = valeur;
                    pred[succs[j]] = i;
                    modif = 1;
                    printf("Le coût du chemin de %d vers %d est %d\n", i, succs[j], couts[succs[j]]);
                }
            }
            libMemTab(&succs);
        }
    }
    libMemTabC(&couts);
    libMemTab(&pred);
}


void dijsktra(int s, MatAdjacence mAdj, int *couts, int *pred){
    
    // Initialisation
    int n = nbSom(mAdj);
    int sommets[n];
    // On instancie un ensemble sommets à 1 pour indique que les sommets ne 
    // sont pas accessibles.
    for(int i = 0; i < n; i++){
        sommets[i] = 1;
    }
    sommets[s] = 0;

    // On initialise le coût des chemins directs depuis le sommet de départ
    // et leur prédeccesseur (le sommet de départ), ainsi que les autres sommets 
    // avec des valeurs absurdes.
    couts = allocTabF(n);
    pred = allocTabF(n);
    for(int i = 0; i < n; i++){
        if(i == s){
            couts[i] = 0;
            pred[i] = s;
        }
        else if(mAdj.mat[s][i] != 0){
            couts[i] = mAdj.cout[s][i];
            pred[i] = s;
            printf("Le coût du chemin de %d vers %d est %d\n", s, i, couts[i]);
        }
        else{
            couts[i] = INT_MAX;
            pred[i] = -1;
        }
    }

    // Itérations
    int sommetAccessible = n-2;
    int accessible = 1;
    TElement m = s;
    while((sommetAccessible > 0) && (accessible)){
        m = coutMin(mAdj, m, sommets);
        if(couts[m] == INT_MAX){
            accessible = 0;
        }
        else{
            sommets[m] = 0;
            sommetAccessible--;
            // Ce tableau est la liste des successeurs du sommet de départ (m).
            TElement *succs;
            succs = allocTabF(n);
            int nbSucc = successeursDijsktra(&succs, mAdj, m, sommets);
            for(int j = 0; j < nbSucc; j++){
                int valeurChemin = couts[m] + mAdj.cout[m][succs[j]];
                if(valeurChemin < couts[succs[j]]){
                    couts[succs[j]] = valeurChemin;
                    pred[succs[j]] = m;
                    printf("Le coût du chemin de %d vers %d est %d\n", m, succs[j], couts[succs[j]]);
                }
            }
        }
    }
    libMemTabInt(&couts);
    libMemTabInt(&pred);
}


void bellman(int s, MatAdjacence mAdj, int *couts, int *pred){
    // Initialisation
    int n = nbSom(mAdj);
    int sommets[n];
    // On instancie un ensemble sommets à 1 pour indiquer que les sommets ne 
    // sont pas accessibles.
    for(int i = 0; i < n; i++){
        sommets[i] = 1;
    }
    sommets[s] = 0;
    

    // On initialie le coût des chemins directs depuis le sommet de départ
    // et leur prédeccesseur (le sommet de départ), ainsi que les autres sommets 
    // avec des valeurs absurdes.
    couts = allocTabF(n);
    pred = allocTabF(n);
    
    for(int i = 0; i < n; i++){
        if(i == s){
            couts[i] = 0;
            pred[i] = s;
        }
        else{
            couts[i] = INT_MAX;
            pred[i] = -1;
        }
    }

    // Itérations jusqu'à qu'on ait exploité tous les sommets
    int nonVideSommets = n;
    while(nonVideSommets){
        puts("");
        TElement *preds = allocTabF(n-1);
        int x = 0;
        int t = choisirSommetsuivant(&preds, sommets, mAdj, &x);
        if(t == -1){
            exit(0);
        }
        sommets[t] = 0;
        nonVideSommets--;
        int m = preds[0];
        int valeurMin = couts[m] + mAdj.cout[m][t];
        // printf("Le coût du chemin de %d à %d est : %d\n", m, t, valeurMin);
        // On compare la distance du chemin avec celle des autres prédécesseurs de t
        for(int u = 1; u < x; u++){
            int tmpValeurChemin = couts[preds[u]] + mAdj.cout[preds[u]][t];
            // printf("Le coût du chemin de %d à %d est : %d\n", preds[u], t, tmpValeurChemin);
            if(tmpValeurChemin < valeurMin){
                valeurMin = tmpValeurChemin;
                m = preds[u];
            }
        }
        couts[t] = valeurMin;
        pred[t] = m;
        printf("Le coût du chemin de %d à %d est : %d\n", pred[t], t, couts[t]);
    }
    libMemTabInt(&couts);
    libMemTabInt(&pred);
}

void floyd(FileSucc fs, int **cout, int **pred){
    int n = fs.nbSom - 1;
    cout = allocMatrice(n);
    pred = allocMatrice(n);
    for(int s = 0; s < n; s++){
        for(int t = 0; t < n; t++){
            int indexArc = arcExiste(s,t,fs);
            if(indexArc != -1){
                cout[s][t] = fs.Cout[indexArc];
                pred[s][t] = s;
            }
            else if(s == t){
                cout[s][t] = 0;
                pred[s][t] = s;
            }
            else{
                cout[s][t] = INT_MAX;
                pred[s][t] = -1;
            }
        }
    }
    affichageCoutPredFS(fs, cout, pred);

    for(int k = 0; k < n; k++){
        for(int s = 0; s < n; s++){
            for(int t = 0; t < n; t++){
                int tmp = cout[s][k] + cout[k][t];
                if(tmp < cout[s][t]){
                    cout[s][t] = tmp;
                    pred[s][t] = pred[k][t];
                }
            }
        }
    }
    affichageCoutPredFS(fs, cout, pred);
}

void affichageCoutPredFS(FileSucc fs, int **couts, int **pred){
    puts("Matrice des coût de chaque arc");
    for(int s = 0; s < fs.nbSom - 1; s++){
        for(int t = 0; t < fs.nbSom - 1; t++){
            printf("%d | ", couts[s][t]);
        }
        puts("");
    }

    puts("Matrice des prédécesseurs de chaque sommet");
    for(int s = 0; s < fs.nbSom - 1; s++){
        for(int t = 0; t < fs.nbSom - 1; t++){
            printf("%d | ", pred[s][t]);
        }
        puts("");
    }
}