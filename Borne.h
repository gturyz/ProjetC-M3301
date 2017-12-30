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

/* Structures */

typedef struct  // une voiture avec des données par défault
{
  char plaque[20];
  char categorie;
  int duree;
}Voiture;

typedef struct
{
  int num_port;
  char ip[20];
  int socket;
}monbeauserveur;

/* Prototypes */

void viderBuffer(); //vide le buffer pour le scanf
float prix_a_payer(char categorie, int duree, int duree_forfait, float prix_forfait, float prix_hors_forfait); //calcul le prix que doit payer une voiture
int ajoutServ( int i , monbeauserveur* mesbeauxserveur); //ajoute un nouveau parking à la liste des parkings

#endif
