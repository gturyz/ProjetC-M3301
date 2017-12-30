#include "Borne.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int ajoutServ( int i , monbeauserveur* mesbeauxserveur ) {

  int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  //		       domaine  type         protocle
  if(s == -1)
    perror("echec de la création de la socket");
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

    printf("Saisir le parking voulu : \n");
    do {
      if(scanf("%d", &nbPark)!=1)
        viderBuffer();
    } while( nbPark <= -1 && nbPark >= nb);
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
    }

    if( f == 2 ) {

    }

  } while( f != 9 );

	//tant que un charactère de fin ne sera pas entré il faut demander si le client veut faire le 2.1 ou le 2.2 du sujet


	return 0;
}
