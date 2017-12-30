#include "Parking.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void ajouterVoiture(Voiture v, Voiture *p)
{
	*p = v;
}

int main()
{
	Voiture list_voiture[nb_voiture];

	ajouterVoiture(v1, &list_voiture[0]);
	ajouterVoiture(v2, &list_voiture[1]);
	ajouterVoiture(v3, &list_voiture[2]);
	ajouterVoiture(v4, &list_voiture[3]);

	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//		       domaine  type         protocle
	if(s == -1)
		perror("echec de la création de la socket\n");
	else
	{
		printf("création réussie de la socket\n");

		//struct server
		struct sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(config.port);
		server.sin_addr.s_addr = inet_addr(config.ip);

		int b = bind(s, (struct sockaddr *)&server, sizeof(server));

		int adr = sizeof(server);
		getsockname(s, (struct sockaddr *)&server,(socklen_t *) &adr);

		if(b == -1)
			perror("echec du bind de la socket\n");
		else
		{
			printf("bind réussi\n");
	  		if(listen(s, 1) == -1)
	  			perror("echec du listen\n");
	  		else
	  		{
	  			printf("reussite du listen\n");
	  			while(1)
	  			{
	  				int s1 = accept(s, NULL, NULL);
	  				if(s1 == -1)
	  					perror("echec du accept\n");
	  				else
	  				{
	  					if(fork() == 0)
							{
	  						printf("reussite du accept\n");
								//suite du code
								int nb;
								//on regarde ce que la borne nous demande de faire
								do {
									if(read(s1, &nb, sizeof(int)) > 0)
									{
										if (nb == 1)
										{
											char cat;
											if(read(s1, &cat, sizeof(char)) > 0) //on lit la catégorie
											{
												int i = cat - 'A';
												write(s1, config.ip, sizeof(config.ip)); //on envoie qui on est
												write(s1, &config.donnees.heure_forfait[i], sizeof(config.donnees.heure_forfait[i])); // on envoie la durée maximale
												write(s1, &config.donnees.prix_forfait[i], sizeof(config.donnees.prix_forfait[i])); // on envoie le prix de l'heure quand on est dans le forfait
												write(s1, &config.donnees.prix_hors_forfait[i], sizeof(config.donnees.prix_hors_forfait[i])); //on envoie le prix de l'heure quand on est hors forfait
											}
											else
												perror("echec du read catégorie");
										}
										if (nb == 2)
										{
												//lire la plaque de la voiture
												//si on a la voiture en stock
													//on envoie 0
													//on dit qui on est
													//on donne la duree de stationnement actuelle
													//on donne la duree du prix_forfait
													//on donne le prix a payer
												//sinon
													//on envoie 1
										}
									}
									else
										perror("echec du read type de demande");
								} while(nb != 9);
							}
	  					else
	  						s1 = accept(s, NULL, NULL);
	  				}
	  			}
	  		}
		}
	}
	return 0;
}
