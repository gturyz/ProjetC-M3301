#include "Borne.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
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

      mesbeauxserveur[i].num_port = port;

      strncpy(mesbeauxserveur[i].ip,ipAdr,15);

			if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
				perror("echec de la connection\n");
			else
				printf("connexion réussie\n");
        mesbeauxserveur[i].socket = s;
		}

	}

  int f = 0;

  do {

    do {
      if(scanf("%d", &f)!=1)
        viderBuffer();
    } while( f != 1 && f != 2 && f != 9 );

    if( f == 1 ) {
      
    }

    if( f == 2 ) {

    }

  } while( f != 9 );

	//tant que un charactère de fin ne sera pas entré il faut demander si le client veut faire le 2.1 ou le 2.2 du sujet


	return 0;
}
