#include <math.h>
#include "op_matInc.h"



int cheminSimpleExiste(TElement e, TElement s, MatIncidence *flot, int index){
    if(e == s){
        return 1;
    }
    if(index < 0){
        return 0;
    }
    else{
        for(int j = 0; j < flot->nbArcs; j++){
            if(flot->mat[e][j] == 1){
                int succ = trouveSucc(j, flot);
                chemin.sommets[index] = succ;
                chemin.nbSommet = index + 1;
                // printf("Successeur de %d est %d\n", e, succ);
                return cheminSimpleExiste(succ, s, flot, ++index);
            }
        }
        /** Si il n'a pas de successeur, on supprime l'arc du graphe résiduel et on cherche 
        un autre chemin. */
        int predecesseur = suppArcSansChemin(e,flot);
        chemin.sommets[index] = 0;
        chemin.nbSommet = index - 1;
        return cheminSimpleExiste(predecesseur, s, flot, --index);
        
    }
}

int suppArcSansChemin(TElement s, MatIncidence *flot){
    for(int i = 0; i < flot->nbArcs; i++){
        // On rend inacessible le sommet s en supprimant son extrémité puis son prédécesseur.
        if(flot->mat[s][i] == -1){
            flot->mat[s][i] = 0;
            for(int j = 0; j < flot->nbSom; j++){
                if(flot->mat[j][i] == 1){
                    flot->mat[j][i] = 0;
                    return j;
                }
                // estLigneSansSommet(s, flot);
            }
        }
    }
}

void estLigneSansSommet(TElement ligne, MatIncidence *flot){
    int sansSommet = 1;
    for(int i = 0; i < flot->nbArcs; i++){
        if(flot->mat[ligne][i] != 0){
            sansSommet = 0;
        }
    }
    if(sansSommet){
        chemin.ligneSansSom[ligne] = 1;
    }
}

int minChemin(MatIncidence *flot, MatIncidence matInc, TElement e){
    int st = trouverColonne(e, chemin.sommets[0], matInc);
    int ligne = trouveSucc(st, flot);
    int flotMin = abs(flot->cout[ligne][st]);
    printf("flot minimum : %d de [%d,%d]\n", flotMin, e, st);

    printf("Nombre de sommets dans chemin %d \n", chemin.nbSommet);
    if(chemin.nbSommet >= 2){
        for(int i = 0; i < chemin.nbSommet - 1; i++){
            TElement s = chemin.sommets[i];
            TElement succ = chemin.sommets[i + 1];
            succ = trouverColonne(s, succ, matInc);
            TElement l = trouveSucc(succ, flot);
            // printf("La colonne de l'arc [%d,%d] est %d\n", l, 
            //     chemin.sommets[i + 1], succ);
            // printf("Le flot possible de [%d,%d] est %d\n", l, succ, flot->cout[l][succ]);
            if(abs(flot->cout[l][succ]) < flotMin){
                flotMin = abs(flot->cout[l][succ]);
                // printf("voici le flot : %d pour [%d,%d]\n", flotMin, s, succ);
            }
        }
    }
    return flotMin;
}

int trouveSucc(TElement col, MatIncidence *flot){
    for(int i = 0; i < flot->nbSom; i++){
        if(flot->mat[i][col] == -1) return i;
    }
}

int trouverColonne(TElement s, TElement succ, MatIncidence mInc){
    int n = mInc.nbArcs;
    int m = mInc.nbSom;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            // si une case est un départ alors on cherche son extrémité dans la colonne
            if(mInc.mat[i][j] == 1 && i == s){
                // printf("[%d,%d]\n",i,j);
                for(int x = 0; x < m; x++){
                    if(mInc.mat[x][j] == -1 && x == succ){
                        // printf("[%d,%d]\n",x,j);
                        return j;
                    }
                }
            }
            // si une case est une extrémité alors on cherche son début dans la colonne
            else if(mInc.mat[i][j] == -1 && i == succ){
                for(int x = 0; x < m; x++){
                    if(mInc.mat[x][j] == 1 && x == s){
                        return j;
                    }
                }
            }
        }
    }
    return -1;
}

void construireGrapheRes(TElement s, MatIncidence *flot, TCout flotMin, MatIncidence mInc){
    for(int i = 0; i < chemin.nbSommet; i++){
        int st = trouverColonne(s, chemin.sommets[i], mInc);
        // si il y a assez de capacité pour faire passer le flot.
        if((flotMin + flot->cout[s][st]) <= mInc.cout[s][st]){
            // flot arc avant
            flot->cout[s][st] += flotMin;
            if(flot->cout[s][st] == mInc.cout[s][st]){
                suppArcGrapheRes(s, st, flot);
            }   
            // flot arc arrière
            for(int i = 0; i < mInc.nbSom; i++){
                if((flotMin + flot->cout[i][st]) <= 0){
                    flot->cout[i][st] += flotMin;
                    if(flot->cout[i][st] == 0)    suppArcGrapheRes(i, st, flot);
                    break;
                }
            }
        }
        s = chemin.sommets[i];
    }
}

void suppArcGrapheRes(TElement s, TElement t, MatIncidence *flot){
    flot->mat[s][t] = 0;
    estLigneSansSommet(s, flot);
}

void affichageGrapheRes(MatIncidence *flot){
    int n = flot->nbSom;
    int na = flot->nbArcs;
    puts("\nAffichage des arcs accessibles du graphe résiduels");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < na; j++){
            printf(" %d |",flot->mat[i][j]);
        }
        printf("\n");
    }
    puts("\nAffichage des coûts du graphe résiduel");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < na; j++){
            printf(" %d |",flot->cout[i][j]);
        }
        printf("\n");
    }
}
