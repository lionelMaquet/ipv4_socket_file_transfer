#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAX_LINE 4096
#define SIZE 1024

void send_file(FILE *fp, int sockfd);
ssize_t total = 0;

int main(int argc, char *argv[])
{
	// DECLARATION DES VARIABLES
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_in *h;
	struct sockaddr_in server_addr;
	int rv, e, sockfd;
	char *ptr; // used by strtol function
	char ip[100];
	FILE *fp;
	char *filename = argv[1]; // le nom du fichier vient des paramètres à l'input (1er argument passé, 2ème dans la liste)
	int port = strtol(argv[3], &ptr, 10); // Conversion du port de string vers int depuis l'input (3ème argument passé, 4ème dans la liste)

	// OBTENTION DE L'IP DU SERVEUR DEPUIS SON HOSTNAME
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ( (rv = getaddrinfo ( argv[2], "http", &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(rv));
		return 1;
	}

	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		h = (struct sockaddr_in *) p->ai_addr;
		strcpy(ip, inet_ntoa(h->sin_addr));
	}
	freeaddrinfo(servinfo);

	// CREATION DU SOCKET
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("[-]Erreur à la création du socket.\n");
		exit(1);
	}
	printf("[+]Socket créé avec succès.\n");

	// CONFIGURATION DE LA STRUCTURE DU SOCKET
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = inet_addr(ip);

	// CONNEXION AU SOCKET
	e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (e == -1) {
		perror("[-]Erreur à la connexion au socket");
		exit(1);
	}
	printf("[+]Connecté au serveur.\n");

	// OUVERTURE DU FICHIER A ENVOYER
	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror("[-]Erreur à la lecture du fichier\n.");
		exit(1);
	}

	// ENVOI DU FICHIER SUR LE SOCKET
	send_file(fp, sockfd);
	printf("[+]Fichier envoyé avec succès.\n");
	printf("[+]Fermeture de la connexion.\n");

	// FERMETURE DU SOCKET
	close(sockfd);

	// FIN DU PROGRAMME
	return 0;

}

void send_file(FILE *fp, int sockfd){

	// DECLARATION DES VARIABLES
	int n;
	char sendline[MAX_LINE] = {0};

	// ENVOI DU FICHIER
	while((n = fread(sendline,sizeof(char),MAX_LINE,fp))>0) {
		total+=n;
		if(n != MAX_LINE && ferror(fp))
		{
			perror("[-]Erreur à la lecture du fichier.\n");
			exit(1);
		}

		if(send(sockfd,sendline, n, 0) == -1) {
			perror("[-]Erreur à l'envoi du fichier.\n");
			exit(1);
		}
		memset(sendline, 0, MAX_LINE);
	}

}
