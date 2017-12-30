#include "Borne.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

float prix_a_payer(char categorie, int duree, int duree_forfait, float prix_forfait, float prix_hors_forfait)
{
	if (duree < duree_forfait)
		return duree * prix_forfait;
	else
		return duree_forfait * prix_forfait + (duree - duree_forfait) * prix_hors_forfait;
}

int ajoutServ( int i , monbeauserveur* mesbeauxserveur)
{

  int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  //		       domaine  type         protocle
  if(s == -1)
  {
    perror("echec de la création de la socket");
    return 0;
  }
  else
  {
    printf("création réussie de la socket\n");

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    int port = 0;
    printf("Saisir le port voulu ( entre  5 500 et 65 500 ) : \n");
    do {
      if(scanf("%d", &port)!=1)
        viderBuffer();
    } while( port >= 65500 || port <= 5500 );

    char ipAdr[15];
    printf("Saisir l'adresse ip voulu : \n");
    do {
      if(scanf("%s", &ipAdr)!=1)
        viderBuffer();
    } while( inet_pton(AF_INET, ipAdr, &(server.sin_addr)) != 1 );

    //struct server
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ipAdr);

    mesbeauxserveur->num_port = port;

    strncpy(mesbeauxserveur->ip,ipAdr,15);

    if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0){
      perror("echec de la connection\n");
      return 0;
    }
    else {
      printf("connexion réussie\n");
      mesbeauxserveur->socket = s;
      return 1;
    }
  }
}

int main()
{

  printf("Combien de parking voulez vous consulter : \n");

  int nb = 0;
  do {
    if(scanf("%d", &nb)!=1)
      viderBuffer();
  } while( nb <= 0 );

	monbeauserveur mesbeauxserveur[nb];

	for(int i = 0; i < nb ; i++){

    if ( ajoutServ(i,&mesbeauxserveur[i]) != 1 )
      i--;

	}

  int f = 0;

  int nbPark = -1;

  do {

    //printf("Saisir le parking voulu : \n"); // plus necessaire car on va
    //do {                                    // demander a tous les parkings
    //  if(scanf("%d", &nbPark)!=1)           // en même temps
    //    viderBuffer();                      //
    //} while( nbPark <= -1 && nbPark >= nb); //
    Voiture voiture;
    printf("Saisir plaque de la voiture : \n");
    while(scanf("%s", &voiture.plaque)!=1){
      viderBuffer();
    }
    write(mesbeauxserveur[nbPark].socket, voiture.plaque, sizeof(voiture.plaque));
    printf("Quel categorie ? A B C D E \n");
    do {
      if(scanf("%s", &voiture.categorie)!=1)
        viderBuffer();
    } while(  voiture.categorie != 'A' &&
              voiture.categorie != 'B' &&
              voiture.categorie != 'C' &&
              voiture.categorie != 'D' &&
              voiture.categorie != 'E');

    do {
      if(scanf("%d", &f)!=1)
        viderBuffer();
    } while( f != 1 && f != 2 && f != 9 );


    if( f == 1 ) {

      printf("Saisir la duree du stationnement envisagé : \n");
      do {
        if(scanf("%d", &voiture.duree)!=1)
          viderBuffer();
      } while( voiture.duree <= 0 );

      //pour TOUS les parking : for
      for (int i = 0; i < nb; i++)
      {
        //envoyer le numero saisit au server en cours
        write(mesbeauxserveur[i].socket, &f, sizeof(f));
        //envoyer la catégorie de la voiture : char
        write(mesbeauxserveur[i].socket, &voiture.categorie, sizeof(voiture.categorie));
        //lire l'ip du serveur : char[20]
        char ip[20];
        read(mesbeauxserveur[i].socket, &ip, sizeof(ip));
        //lire la duree du forfait : int
        int duree_forfait;
        read(mesbeauxserveur[i].socket, &duree_forfait, sizeof(duree_forfait));
        //lire le prix_forfait : float
        float prix_forfait;
        read(mesbeauxserveur[i].socket, &prix_forfait, sizeof(prix_forfait));
        //lire le prix_hors_forfait float
        float prix_hors_forfait;
        read(mesbeauxserveur[i].socket, &prix_hors_forfait, sizeof(prix_hors_forfait));
        //faire le calcul magique : on passera par une fonction (a faire)
        float cout = prix_a_payer(voiture.categorie, voiture.duree, duree_forfait, prix_forfait, prix_hors_forfait);
        //afficher le cout pour la durée demandée : ex : pour 2h
        printf("Pour le parking %s et une durée de %d, le cout est de %f\n", ip, voiture.duree, cout);
        //afficher le cout pour la durée + 1 h : ex : pour 2+1=3h
        cout = prix_a_payer(voiture.categorie, voiture.duree+1, duree_forfait, prix_forfait, prix_hors_forfait);
        printf("Pour le parking %s et une durée de %d + 1 heure, le cout est de %f\n", ip, voiture.duree, cout);
        //afficher le cout pour la durée double : ex : pour 2*2=4h
        cout = prix_a_payer(voiture.categorie, voiture.duree*2, duree_forfait, prix_forfait, prix_hors_forfait);
        printf("Pour le parking %s et une durée de %d x 2, le cout est de %f\n", ip, voiture.duree, cout);
      }
    }

    if( f == 2 ) {
      //pour TOUS les parking : for
      for (int i = 0; i < nb; i++)
      {
        //envoyer le numero saisit au server en cours
        write(mesbeauxserveur[i].socket, &f, sizeof(f));
        //lire un entier : int
        int rep = -1;
        read(mesbeauxserveur[i].socket, &rep, sizeof(int));
        //si l'entier vaut 0
        if (rep == 0)
        {
          //lire l'ip du serveur : char[20]
          char ip[20];
          read(mesbeauxserveur[i].socket, &ip, sizeof(ip));
          //lire la durée de stationnement actuelle : int
          int duree_stationnement;
          read(mesbeauxserveur[i].socket, &duree_stationnement, sizeof(duree_stationnement));
          //lire la durée du forfait : int
          int duree_forfait;
          read(mesbeauxserveur[i].socket, &duree_forfait, sizeof(duree_forfait));
          //lire le prix a payer : float
          float cout;
          read(mesbeauxserveur[i].socket, &cout, sizeof(cout));
          //afficher les infos
          printf("Pour le parking %s, la voiture %s est stationnée depuis %d heures.\nLe cout est de %f\n", ip, voiture.plaque, duree_stationnement, cout);
        }
      }
    }

  } while( f != 9 );

	//tant que un charactère de fin ne sera pas entré il faut demander si le client veut faire le 2.1 ou le 2.2 du sujet


	return 0;
}
