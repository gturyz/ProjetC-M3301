Projet: menu.o donnees_partie.o utilitaire.o partie.o jeu.o main.o
	gcc -o Projet parking.o borne.o -Wall
	rm -rf *.o

windows: parking.o borne.o
	gcc -o Projet parking.o borne.o -Wall
	del *.o

parking.o: Parking.c
	gcc -o parking.o -c Parking.c -Wall

borne.o: Borne.c
	gcc -o borne.o -c Borne.c -Wall

clear:
	rm -rf *.o
