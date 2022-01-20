#include "allocation.h"

// Allocation mémoire d'un tableau de TElement sous forme de fonction.
TElement *allocTabF (int n){
    TElement *tab; // tab est un pointeur qui pointe nulle part
    tab = (TElement *)malloc(n*sizeof(TElement)); 
    // tab contient maintenant l'adresse du premier élément du tableau.
    if(tab == NULL){
        perror("\n Il y a eu un problème d'allocation mémoiredu tableau.");
        exit(0);
    }
    return tab;
}

// Allocation mémoire d'un tableau de TCout sous forme de fonction.
TCout *allocTabCout(int n){
    TCout *tab;
    tab = (TCout *)malloc(n*sizeof(TCout));
    if(tab == NULL){
        perror("\n Il y a eu un problème d'allocation mémoiredu tableau.");
        exit(0);
    }
    return tab;
}

// Allocation mémoire d'un tableau de int sous forme de fonction.
int *allocTabInt(int n){
    int *tab;
    tab = (int *)malloc(n * sizeof(int));
    if(tab == NULL){
        perror("\n Il y a eu un problème d'allocation mémoiredu tableau.");
        exit(0);
    }
    return tab;
}

// Permet de libérer la mémoire d'un tableau de TElement
void libMemTab(TElement **tab){
    free(*tab);
    // forcer la libération de la mémoire
    *tab = NULL;
}

// Permet de libérer la mémoire d'un tableau de TCout
void libMemTabC(TCout **cout){
    free(*cout);
    *cout = NULL;
}

// Permet de libérer la mémoire d'un tableau de int
void libMemTabInt(int **tab){
    free(*tab);
    *tab = NULL;
}

// Permet d'allouer de la mémoire pour la matrice à 2 dimensions
TElement **allocMatF(int n, int m){
    TElement **mat;
    // Allocation mémoire du tableau d'adresses.
    mat = (TElement **)malloc(n*sizeof(TElement*));
    // printf("adresse de mat : %p\n", mat);
    if(mat == NULL){
        printf("\n Il y a eu un problème d'allocation mémoire de la matrice.");
        exit(0);
    }
    // Allocation mémoire pour chaque ligne de la matrice (chaque élément de mat).
    for(int i = 0; i < n; i++){
        mat[i] = allocTabF(m); // appel de fonction
        // printf("adresse de chaque colonne de mat = %p\n", *mat);
    }
    return mat;
}

TCout **allocCoutF(int n, int m){
    TCout **cout;
    cout = (TCout **)malloc(n * sizeof(TCout*));
    // printf("adresse de cout = %p\n", cout);
    if(cout == NULL){
        printf("\n Il y a eu un problème d'allocation mémoire des couts de la matrice.");
        exit(0);
    }
    for(int i = 0; i < n; i++){
        cout[i] = allocTabCout(m);
        // printf("adresse de colonne de cout = %p\n", *cout);
    }
    return cout;
}

// On libère la mémoire d'une matrice.
void libMemMatP(int nblig, TElement ***mat, TCout ***cout){
    // Libération de chaque ligne de la matrice.
    for(int i = 0; i < nblig; i++){
        libMemTab(&(*mat[i]));
        libMemTabC(&(*cout[i]));
    }
    // On libère la matrice = libération du tableau d'adresses.
    free(*mat);
    *mat = NULL;
    free(*cout);
    *cout = NULL;
}

// On alloue la mémoire pour la structure de matrice d'adjacence.
MatAdjacence allocMatAdjF(int nMax){
    MatAdjacence mAdj;
    mAdj.nbSom = nMax;
    //appel sous forme de fonction d'allocation matricielle
    mAdj.mat = allocMatF(nMax, nMax);
    // printf("adresse de mAdj.mat = %p\n", mAdj.mat);
    mAdj.cout = allocCoutF(nMax, nMax);
    // printf("adresse de mAdj.cout = %p\n", mAdj.cout);
    return mAdj;
}

// Allocation de la structure de la matrice d'incidence sous forme d'une fonction.
MatIncidence allocMatIncF(int n, int p){
    MatIncidence mInc;
    mInc.nbSom = n;
    mInc.nbArcs = p;
    mInc.mat = allocMatF(n, p);
    mInc.cout = allocCoutF(n, p);
    return mInc;
}

// La libération mémoire occupée par la structure de la matrice
// d'adjacence équivaut à la libération de la matrice contenue
// dans la structure
void libMatAdj(MatAdjacence *mAdj){
    libMemMatP(mAdj->nbSom, &(mAdj->mat), &(mAdj->cout));
}

void libMatInc(MatIncidence *mInc){
    libMemMatP(mInc->nbSom, &(mInc->mat), &(mInc->cout));
}

// Alloue la mémoire de la file des successeurs sous forme de fonction.
FileSucc allocFileSucc(int nbSommets, int nbArcs){
    FileSucc fs;
    fs.nbSom = nbSommets;
    fs.nbArcs = nbArcs;
    fs.APS = allocTabInt(nbSommets);
    fs.FS = allocTabF(nbArcs);
    fs.Cout = allocTabCout(nbArcs);
    return fs;
}

// Libère la mémoire de la file des successeurs sous forme de procédure.
void libFileSucc(FileSucc *fs){
    libMemTabInt(&(fs->APS));
    libMemTab(&(fs->FS));
    libMemTabC(&(fs->Cout));
}

// Alloue la mémoire d'un tableau à 2 dimensions.
int **allocMatrice(int n){
    int **mat;
    mat = (int **)malloc(n * sizeof(int*));
    if(mat == NULL){
        puts("Problème d'allocation mémoire de la matrice");
        exit(0);
    }
    for(int i = 0; i < n; i++){
        mat[i] = allocTabInt(n);
    }
    return mat;
}

// Libère la mémoire d'un tableau de int à 2 dimensions.
void libMemMatrice(int ***mat, int nblig){
    for(int i = 0; i < nblig; i++){
        libMemTabInt(&(*mat[i]));
    }
    free(*mat);
    *mat = NULL;
}

// Crée une cellule avec son sommet successeur et son cout (de l'arc ou arête).
Liste creatCellule(){
    Liste cel;
    cel = (Liste)malloc(sizeof(struct cellule));
    if(cel == NULL){
        perror("Problème d'allocation mémoire");
        exit(0);
    }
    return cel;
}


// Alloue la mémoire pour la liste d'adjacences.
ListAdjacence allocListAdjacence(int nbSom){
    ListAdjacence la;
    la.tabAdj = (Liste*)malloc(nbSom * sizeof(Liste));
    la.nbSom = nbSom;
    return la;
}