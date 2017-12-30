#ifndef BORNE_H
#define BORNE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

typedef struct  // une voiture avec des données par défault
{
  char plaque[20];
  char categorie;
  int duree;
}voiture;

typedef struct
{
  int num_port;
  char ip[20];
  int socket;
}monbeauserveur;



#endif
