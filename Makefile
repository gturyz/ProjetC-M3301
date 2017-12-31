Projet: parking.o borne.o
	gcc -o Parking parking.o -Wall
	gcc -o Borne borne.o -Wall
	rm -rf *.o

windows: parking.o borne.o
	gcc -o Parking parking.o -Wall
	gcc -o Borne borne.o -Wall
	del *.o

parking.o: Parking.c
	gcc -o parking.o -c Parking.c -Wall

borne.o: Borne.c
	gcc -o borne.o -c Borne.c -Wall

clear:
	rm -rf *.o
