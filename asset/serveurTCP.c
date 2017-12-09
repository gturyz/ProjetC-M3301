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
	Calcul operation;
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
		server.sin_port = htons(1025);
		server.sin_addr.s_addr = inet_addr("192.168.4.235");
		
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
						long buf;
						if(read(s1, &buf, 8) > 0) 
							operation.arg1 = buf;
						else
							perror("echec du read1");
						if(read(s1, &buf, 1) > 0) 
							operation.op = buf;
						else
							perror("echec du read2");
						if(read(s1, &buf, 8) > 0) 
							operation.arg2 = buf;
						else
							perror("echec du read3");
						long rep;
						switch(operation.op)
						{
							case '+':
							{
								rep = operation.arg1 + operation.arg2;						
								break;
							}
							case '-':
							{
								rep = operation.arg1 - operation.arg2;						
								break;
							}
							case '/':
							{
								rep = operation.arg1 / operation.arg2;						
								break;
							}
							case '*':
							{
								rep = operation.arg1 * operation.arg2;						
								break;
							}
							default :
							{
								write(s1, "mauvais operateur\n", 18);					
							}
						}
						printf("argument 1 : %ld\n", operation.arg1);
						printf("operateur : %c\n", operation.op);
						printf("argument 2 : %ld\n", operation.arg2);
						printf("resultat : %ld\n", rep); 

						write(s1, &rep, sizeof(rep));
					}
					else
					{
						s1 = accept(s, NULL, NULL);
					}
				}
			}
		}
		}		
	}
	//sleep(60);	
	return 0;	
}
