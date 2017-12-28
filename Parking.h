#ifndef PARKING_H
#define PARKING_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct Voiture Voiture;

struct voiture // une voiture avec des données par défault
{
  char plaque[] = "AA-111-AA";
  char categorie = 'A';
  int duree = 1;
};

typedef struct Parking Parking;

struct Parking // un parking avec des données par défault
{
  int nb_place[] = {0, 1, 0, 1};
  int heure_forfait[] = {2, 4, 6, 8};
  float prix_forfait[] = {1.5, 2, 2.5, 3, 3.5};
  float prix_hors_forfait[] = {5, 10, 15, 20, 25};
};

typedef struct Configuration Configuration;

struct Configuration // un server avec des données par défault
{
  int port = 8000;
  char ip[] = "127.0.0.1";
  Parking donnees;
};

#endif
