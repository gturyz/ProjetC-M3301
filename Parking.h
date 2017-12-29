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

//création de la structure stockant les données du serveur
Configuration config = {8001, "127.0.0.1", {{0, 1, 0, 1},{2, 4, 6, 8},{1.5, 2, 2.5, 3, 3.5},{5, 10, 15, 20, 25}}};
Voiture list_voiture[] = { , , , }

#endif
