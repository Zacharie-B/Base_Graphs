#include "creer_graphe.h"

FileSucc chargFileSucc(char *nomFich){
    int nbSommets, nbArcs;
    FILE *fe;

    // printf("Valeur de la variable : %s", nomFich);
    fe = fopen(nomFich, "r");
    if(fe == NULL){
        perror("problème d'ouverture du fichier en lecture");
        exit(0);
    }

    fscanf(fe, "#Graphe = Matrice d'adjacences et ses dérivées");
    fscanf(fe, "\nNombre de sommets = %d", &nbSommets);
    fscanf(fe, "\nNombre d'arcs = %d", &nbArcs);

    printf("Nombre de sommets : %d et nombre d'arcs : %d\n", nbSommets, nbArcs);
    FileSucc fs = allocFileSucc(nbSommets + 1, nbArcs);
    initFileSucc(nbSommets, nbArcs, &(*fs.APS), &(*fs.FS), &(*fs.Cout), 0);

    int cout, s, nbSucc, t, numArc = 0;
    for(int i = 0; i < nbSommets; i++){
        // Lecture des sommets et successeurs de ceux-ci, pour les ranger dans la matrice.
        fscanf(fe, "\nSommet = %d nbSucc = %d Succ = ", &s, &nbSucc);
        if(s > 0)   fs.APS[s + 1] = fs.APS[s] + nbSucc;
        else{
            fs.APS[s] = 0;
            fs.APS[s + 1] = nbSucc;
        }
        for(int j = 0; j < nbSucc; j++){
            fscanf(fe, "%d ", &t);
            fscanf(fe, "%d ", &cout);
            fs.FS[numArc] = t;
            fs.Cout[numArc] = cout;
            numArc++;
        }
    }
    affichageFileSucc(fs);
    //Lecture de la fin du fichier et fermeture du point de lecture.
    fscanf(fe, "\n#FIN\n");
    fclose(fe);
    
    return fs;
}

void initFileSucc(int nbSommets, int nbArcs, int *APS, TElement *FS, TCout *cout, int valeur){
    for(int i = 0; i < nbSommets; i++){
        APS[i] = valeur;
    }
    for(int j = 0; j < nbArcs; j++){
        FS[j] = valeur;
        cout[j] = valeur;
    }
}

void affichageFileSucc(FileSucc fs){
    int nbSom = fs.nbSom;
    puts("Voici le tableau APS de la file des successeurs");
    for(int i = 0; i < nbSom; i++){
        printf("%d | ", fs.APS[i]);
    }
    puts("\nVoici le tableau des successeurs");
    int nbArcs = fs.nbArcs;
    for(int j = 0; j < nbArcs; j++){
        printf("%d | ", fs.FS[j]);
    }
    puts("\nVoici le tableau du coût de chaque arc");
    for(int j = 0; j < nbArcs; j++){
        printf("%d | ", fs.Cout[j]);
    }
    puts("");
}

MatAdjacence chargMatAdj(char *nomFich){
    int i, j, n, p, s, nbSucc, t;
    FILE *fe;
    MatAdjacence mAdj;

    // Ouverture du fichier en lecture seule.
    fe = fopen(nomFich, "r");
    if(fe == NULL){
        perror("problème d'ouverture du fichier en lecture");
        exit(0);
    }

    // Lecture des éléments du fichier.
    fscanf(fe, "#Graphe = Matrice d'adjacences et ses dérivées");
    fscanf(fe, "\nNombre de sommets = %d", &n);
    fscanf(fe, "\nNombre d'arcs = %d", &p);

    printf("Nombre de sommets : %d et nombre d'arcs : %d\n", n, p);

    // Allocation mémoire pour faire la matrice d'adjacence.
    mAdj = allocMatAdjF(n);
    // Initialisation des coeffs de la matrice à 0.
    initMat(n, n, &(*mAdj.mat), &(*mAdj.cout), 0);
    int cout;
    for(i = 0; i < n; i++){
        // Lecture des sommets et successeurs de ceux-ci, pour les ranger dans la matrice.
        fscanf(fe, "\nSommet = %d nbSucc = %d Succ = ", &s, &nbSucc);
        for(j = 0; j < nbSucc; j++){
            fscanf(fe, "%d ", &t);
            fscanf(fe, "%d ", &cout);
            mAdj.mat[s][t] = 1;
            mAdj.cout[s][t] = cout;
        }
    }
    affichageMatAdj(mAdj);
    //Lecture de la fin du fichier et fermeture du point de lecture.
    fscanf(fe, "\n#FIN\n");
    fclose(fe);
    
    return mAdj;
}

int nbSom(MatAdjacence g){
    return g.nbSom;
}

void initMat(int x, int y, TElement **mat, TCout **cout, int valeur){
    for(int index = 0; index < x; index++){
        for(int indix = 0; indix < y; indix++){
            // printf("adresse de cout[index][indix] : %p\n", &cout[index][indix]);
            // printf("adresse de mat[index][indix] : %p\n", &mat[index][indix]);
            mat[index][indix] = valeur;
            cout[index][indix] = valeur;
        }
    }
}

void affichageMatAdj(MatAdjacence mAdj){
    int n = nbSom(mAdj);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf(" %d |", mAdj.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf(" %d |", mAdj.cout[i][j]);
            
        }
        printf("\n");
    }
    printf("\n");
}

ListAdjacence chargeListAdjacence(char *nomFichier){
    int nbSommets, nbArcs;
    FILE *fe;

    fe = fopen(nomFichier, "r");
    if(fe == NULL){
        perror("problème d'ouverture du fichier en lecture");
        exit(0);
    }

    fscanf(fe, "#Graphe = Liste d'adjacences et ses dérivées");
    fscanf(fe, "\nNombre de sommets = %d", &nbSommets);
    fscanf(fe, "\nNombre d'arcs = %d", &nbArcs);

    puts("############################################################");
    puts("Création de la liste d'adjacence représentant le graphe");
    printf("Nombre de sommets : %d et nombre d'arcs : %d\n", nbSommets, nbArcs);

    ListAdjacence ladj = allocListAdjacence(nbSommets);

    int s, nbSuccs;
    TElement succ;
    TCout cout;
    for(int i = 0; i < nbSommets; i++){
        fscanf(fe, "\nSommet = %d nbSucc = %d Succ =", &s, &nbSuccs);
        // Liste intermédiaire pour gérer les adresses.
        Liste l = NULL;
        for(int j = 0; j < nbSuccs; j++){
            fscanf(fe, " %d %d", &succ, &cout);
            l = inserQueue(l, succ, cout);
            // printf("Adresse de l : %p\n", l);
        }
        ladj.tabAdj[s] = l;
    }
    afficheListeAdjacences(ladj);

    fscanf(fe,"\n#FIN");
    fclose(fe);
    return ladj;
}

// Renvoi l'adresse de la dernière cellule de la liste
Liste dernier(Liste l){
    Liste der = l;
    while(der->suiv != NULL){
        der = der->suiv;
    }
    return der;
}


Liste inserQueue(Liste l, TElement somSucc, TCout cout){
    // La cellule suivante de la dernière est la nouvelle cellule.
    Liste der = NULL;
    if(l == NULL){
        l = creatCellule();
        l->somSucc = somSucc;
        l->cout = cout;
        l->suiv = NULL;
    }
    else{
        der = dernier(l);
        Liste nouvCellule = der->suiv;
        nouvCellule = creatCellule();
        nouvCellule->somSucc = somSucc;
        nouvCellule->cout = cout;
        nouvCellule->suiv = NULL; 
        der->suiv = nouvCellule;
    }
    
    // printf("Adresse de l : %p et adresse de der : %p\n", l, der);
    // printf("La cellule a %d en successeur avec le cout %d.\n", der->somSucc, der->cout);
    return l;
}

void afficheListeAdjacences(ListAdjacence ladj){
    int n = ladj.nbSom;
    for(int i = 0; i < n; i++){
        Liste l = ladj.tabAdj[i];
        afficheListeSucc(l, i);
    }
}

void afficheListeSucc(Liste l, int sommet){
    if(l != NULL){
        // printf("Le sommet %d possède l'adresse %p\n", sommet, l);
        printf("%d --> %d, cout : %d\n", sommet, l->somSucc, l->cout);
        afficheListeSucc(l->suiv, sommet);
    }
}

MatIncidence chargMatInc(char *nomFichier){
    FILE *fd;
    fd = fopen(nomFichier, "r");

    if(fd == NULL){
        perror("problème d'ouverture du fichier en lecture");
        exit(0);
    }

    int n, p;
    // Lecture des éléments du fichier.
    fscanf(fd, "#Graphe = Matrice d'incidence et ses dérivées");
    fscanf(fd, "\nNombre de sommets = %d", &n);
    fscanf(fd, "\nNombre d'arcs = %d", &p);

    printf("Nombre de sommets : %d et nombre d'arcs : %d\n", n, p);

    MatIncidence matInc = allocMatIncF(n, p);

    matInc.nbSom = n;
    matInc.nbArcs = p;

    int nbSuccs, numColonne = 0;
    TCout cout;
    TElement succ, sommet; 
    for(int i = 0; i < n; i++){
        fscanf(fd, "\nSommet = %d nbSucc = %d", &sommet, &nbSuccs);
        fscanf(fd, " Succ = ");
        for(int j = 0; j < nbSuccs; j++){
            fscanf(fd, "%d %d ", &succ, &cout);
            matInc.mat[sommet][numColonne] = 1;
            matInc.mat[succ][numColonne] = -1;
            matInc.cout[sommet][numColonne] = cout;
            matInc.cout[succ][numColonne] = -cout;
            numColonne++;
        }
    }

    affichageMatIncidences(matInc);

    fscanf(fd, "\n#FIN\n");
    fclose(fd);

    return matInc;
}

void affichageMatIncidences(MatIncidence matInc){
    int n = matInc.nbSom;
    int na = matInc.nbArcs;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < na; j++){
            printf(" %d |",matInc.mat[i][j]);
        }
        printf("\n");
    }
    puts("\nMatrice d'incidence des coûts");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < na; j++){
            printf(" %d |",matInc.cout[i][j]);
        }
        printf("\n");
    }
}
