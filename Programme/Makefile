all:pcc1

allocation.o: allocation.c allocation.h
	gcc -c allocation.c

creer_graphe.o: creer_graphe.c creer_graphe.h
	gcc -c creer_graphe.c
	
op_matrice.o: op_matrice.c op_matrice.h
	gcc -c op_matrice.c

pcc1.o: pcc1.c pcc1.h
	gcc -c pcc1.c

pcc1: allocation.o op_matrice.o creer_graphe.o pcc1.o
	gcc allocation.o op_matrice.o creer_graphe.o pcc1.o -o pcc1

op_liste.o: op_liste.c op_liste.h
	gcc -c op_liste.c

arbre_rec.o: arbre_recouv.c arbre_recouv.h
	gcc -c arbre_recouv.c

arbre_rec: arbre_rec.o creer_graphe.o allocation.o op_liste.o
	gcc allocation.o arbre_recouv.o creer_graphe.o op_liste.o -o arbre_rec

flot.o: flot.c flot.h
	gcc -c flot.c

op_matInc.o: op_matInc.c op_matInc.h
	gcc -c op_matInc.c

flot: flot.o creer_graphe.o allocation.o op_matInc.o
	gcc flot.o creer_graphe.o allocation.o op_matInc.o -o flot

clean:
	rm -f allocation.o op_matrice.o creer_graphe.o pcc1.o pcc1 arbre_rec.o arbre_rec flot.o op_matInc.o flot