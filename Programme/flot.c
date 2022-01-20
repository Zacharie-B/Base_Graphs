#include "flot.h"



int main(){
    MatIncidence matInc = chargMatInc("donnees_graphe/ford_fulkerson.txt");
    int flot = fordFulkerson(0, 5, matInc);
    puts("\n#################################################");
    printf("Le flot maximum trouvé est %d.\n", flot);
    puts("\n#################################################");
    return 0;
}

int fordFulkerson(TElement e, TElement s, MatIncidence matInc){
    int n = matInc.nbSom;
    int p = matInc.nbArcs;

    MatIncidence *flot;
    flot = (MatIncidence*)malloc(sizeof(MatIncidence));
    flot->nbSom = n;
    flot->nbArcs = p;
    *flot = allocMatIncF(n, p);

    // Initialisation
    for(int i = 0;  i < n; i++){
        for(int j = 0; j < p; j++){
            // On initialise le graphe d'écart (résiduel).
            if(matInc.cout[i][j] >= 0)  flot->cout[i][j] = 0;           
            else    flot->cout[i][j] = matInc.cout[i][j];
            flot->mat[i][j] = matInc.mat[i][j];
        }
        chemin.ligneSansSom[i] = 0;
    }
    int flotActuel = 0;
    chemin.nbSommet = 0;

    // Itérations
    while(cheminSimpleExiste(e,s,flot,0)){
        int capaciteResiduel = minChemin(flot, matInc, e);
        puts("\n#################################################");
        printf("Le flot minimal du chemin est %d\n", capaciteResiduel);
        affichageChemin(e);
        flotActuel += capaciteResiduel;

        construireGrapheRes(e, flot, capaciteResiduel, matInc);
        affichageGrapheRes(flot);
        chemin.nbSommet = 0;
        puts("\n#################################################");
    }
    return flotActuel;
}

void affichageChemin(TElement e){
    printf("Chemin : %d ", e);
    for(int i = 0; i < chemin.nbSommet; i++){
        printf("-> %d ", chemin.sommets[i]);
    }
    puts("");
}