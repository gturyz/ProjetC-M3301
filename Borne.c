#include "Borne.h"

int main()
{
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		       domaine  type         protocle
	if(s == -1)
		perror("echec de la création de la socket");
	else
	{
		printf("création réussie de la socket\n");

		//struct server
		struct sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(1025);
		server.sin_addr.s_addr = inet_addr("192.168.4.235");

		if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
			perror("echec de la connection\n");
		else
			printf("connexion réussie\n");
	}
	return 0;
}
