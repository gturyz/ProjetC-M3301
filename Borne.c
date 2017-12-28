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
{//demander à combien de serveur il faut que la borne se connecte : int nb

	//monbeauserveur mesbeauxserveur[nb];

	//for(i < nb)

		int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//		       domaine  type         protocle
		if(s == -1)
			perror("echec de la création de la socket");
		else
		{
			printf("création réussie de la socket\n");

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
				printf("%s\n", ipAdr);
			} while( inet_pton(AF_INET, ipAdr, &(server.sin_addr)) != 1 );

			//struct server
			struct sockaddr_in server;
			server.sin_family = AF_INET;
			server.sin_port = htons(port);
			server.sin_addr.s_addr = inet_addr(ipAdr);

			//mettre le port et l'ip dans mesbeauxserveur[i]

			if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
				perror("echec de la connection\n");
			else
				printf("connexion réussie\n");
				//mettre la socket s dans mesbeauxserveur[i]
		}

	//fin for

	//tant que un charactère de fin ne sera pas entré il faut demander si le client veut faire le 2.1 ou le 2.2 du sujet


	return 0;
}
