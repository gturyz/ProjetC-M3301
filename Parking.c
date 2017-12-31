#include "Parking.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int comparerChaine(char s1[20], char s2[20])
{
  int i = 0 , res = 0;
  while (s1[i] != '\0' || s2[i] != '\0')
  {
      if (s1[i] == s2[i])
        i ++;
      else
        res ++;
  }
  return res;
}

void ajouterVoiture(Voiture v, Voiture* p)
{
	*p = v;
}

float prix_a_payer(char categorie, int duree, Configuration* p)
{
	if (duree < p->donnees.heure_forfait[categorie - 'A'])
		return duree * p->donnees.prix_forfait[categorie - 'A'];
	else
		return p->donnees.heure_forfait[categorie - 'A'] * p->donnees.prix_forfait[categorie - 'A'] + (duree - p->donnees.heure_forfait[categorie - 'A']) * p->donnees.prix_hors_forfait[categorie - 'A'];
}

int main()
{
	Voiture list_voiture[nb_voiture];

	ajouterVoiture(v1, &list_voiture[0]);
	ajouterVoiture(v2, &list_voiture[1]);
	ajouterVoiture(v3, &list_voiture[2]);
	ajouterVoiture(v4, &list_voiture[3]);
  ajouterVoiture(v5, &list_voiture[4]);

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
  					printf("reussite du accept\n");
						//suite du code
						int nb;
						//on regarde ce que la borne nous demande de faire
						do
            {
              printf("en attente de la borne\n");
							if(read(s1, &nb, sizeof(int)) > 0)
							{
								if (nb == 1)
								{
                  printf("type de demande : etude de contrat\n");
									char cat;
									if(read(s1, &cat, sizeof(char)) > 0) //on lit la catégorie
									{
                    printf("envoie de données\n");
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
                  printf("type de demande : consultation\n");
									char plaque[20];
									//lire la plaque de la voiture
                  int x = 0;
                  do { //tentative de read sécurisé = echec
                    x += read(s1, &plaque, sizeof(char));
                    printf("test\n");
                  } while(x < 20 || plaque[x] != '\0');

                  if(x > 20)
                  {
                    printf("Echec du read de la plaque\n");
                    int rep = 1;
                    write(s1, &rep, sizeof(int));
                  }
                  else
                  {
                    //on dit qui on est
                    write(s1, config.ip, sizeof(config.ip));
                    for (int i = 0; i < nb_voiture; i++)
                    {
                      //si on a la voiture en stock
                      if (comparerChaine(list_voiture[i].plaque, plaque) == 0)
                      {
                        printf("voiture trouvée\n");
                        //on envoie 0
                        int rep = 0;
                        write(s1, &rep, sizeof(int));
                        //on donne la duree de stationnement actuelle
                        write(s1, &list_voiture[i].duree, sizeof(list_voiture[i].duree));
                        //on donne la duree du forfait
                        int j = list_voiture[i].categorie - 'A';
                        write(s1, &config.donnees.prix_forfait[j], sizeof(config.donnees.prix_forfait[j]));
                        //on donne le prix a payer
                        float prix = prix_a_payer(list_voiture[i].categorie, list_voiture[i].duree, &config);
                        write(s1, &prix, sizeof(float));
                      }
                      //sinon
                      else
                      {
                        printf("voiture non trouvée\n");
                        //on envoie 1
                        int rep = 1;
                        write(s1, &rep, sizeof(int));
                      }
                    }
                  }
								}
									else
										perror("echec du read plaque");
							}
							else
              {
								perror("echec du read type de demande");
                nb = 9;
              }
						} while(nb != 9);
            close(s1);
            close(s);
            return 0;
          }
				}
			}
		}
	}
  return 0;
}
