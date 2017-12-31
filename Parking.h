#ifndef PARKING_H
#define PARKING_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/* Structures */

typedef struct voiture Voiture;

struct voiture // une voiture
{
  char plaque[20];
  char categorie;
  int duree;
};

typedef struct Parking Parking;

struct Parking // un parking
{
  int nb_place[5];
  int heure_forfait[5];
  float prix_forfait[5];
  float prix_hors_forfait[5];
};

typedef struct Configuration Configuration;

struct Configuration // un server
{
  int port;
  char ip[20];
  Parking donnees;
};

/* Prototypes */

void viderBuffer(); //vide le buffer pour le scanf
void ajouterVoiture(Voiture v, Voiture*p); //ajoute la voiture à la liste des voitures du serveur
float prix_a_payer(char categorie, int duree, Configuration* p); //calcul le prix que doit payer une voiture

/* Variables */

//création de la structure stockant les données du serveur
Configuration config = {
  8007,
  "127.0.0.1",
  {
    {0, 1, 0, 1},
    {2, 4, 6, 8},
    {1.5, 2, 2.5, 3, 3.5},
    {5, 10, 15, 20, 25}}
};

//initilisation du stockage des voitures
int nb_voiture = 4;

Voiture v1 ={"AA-AAA-AA", 'A', 1};
Voiture v2 ={"BB-BBB-BB", 'B', 2};
Voiture v3 ={"CC-CCC-CC", 'C', 3};
Voiture v4 ={"DD-DDD-DD", 'D', 4};
Voiture v5 ={"A", 'A', 1};

#endif
