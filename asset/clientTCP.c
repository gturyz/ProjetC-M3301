#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef struct 
{
	long arg1;
	char op;
	long arg2;
}Calcul;

int main()
{
	int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//		       domaine  type         protocle
	if(s == -1)
		perror("echec de la création de la socket");
	else
	{
		printf("création réussie de la socket\n");
		
		Calcul operation;

		operation.arg1 = 2;
		operation.op = '+';
		operation.arg2 = 2;
	
		//struct server
		struct sockaddr_in server;
		server.sin_family = AF_INET;
		server.sin_port = htons(1025);
		server.sin_addr.s_addr = inet_addr("192.168.4.235");		

		if(connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
			perror("echec de la connection\n");
		else
		{
			printf("connexion réussie\n");

			write(s, (struct Calcul*)&operation, sizeof(operation));
			//write(s, (struct Calcul*)&operation.op, 1);
			//write(s, (struct Calcul*)&operation.arg2, 1);

			long buf;
			int count = read(s, &buf, sizeof(buf));
			printf("%d recu : %ld\n", count, buf);
		}
	}
	//sleep(60);	
	return 0;	
}

