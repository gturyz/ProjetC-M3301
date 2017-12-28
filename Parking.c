#include "Parking.h"

int main()
{
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		       domaine  type         protocle
	if(s == -1)
		perror("echec de la création de la socket\n");
	else
	{
		printf("création réussie de la socket\n");

		//création de la structure stockant les données du serveur
		Configuration config;

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
	  						printf("reussite du accept\n");
								//suite du code
								printf("c'est déjà bien\n");
	  					else
	  						s1 = accept(s, NULL, NULL);
	  				}
	  			}
	  		}
		}
	}
	return 0;
}
