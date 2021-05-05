#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 1024
#define MAX_LINE 4096

ssize_t total = 0;
void write_file(int sockfd, FILE *fp);

int main(int argc, char *argv[]){

	// DECLARATION DES VARIABLES
	char *ptr; 
	char buffer[SIZE];
	int port, e, sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	port = strtol(argv[2], &ptr, 10);

	// CREATION DU SOCKET
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("[-]Erreur à la création du socket.\n");
		exit(1);
	}
	printf("[+]Socket créé avec succès.\n");

	// CONFIGURATION DU SOCKET
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = port;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// CONNEXION AU SOCKET
	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (e < 0) {
		perror("[-]Erreur à la connexion au socket.\n");
		exit(1);
	}
	printf("[+]Connecté au socket avec succès.\n");

	// ECOUTE DU SOCKET
	if (listen(sockfd, 10) == 0){
		printf("[+]En attente d'un client ... \n");
	} else {
		perror("[-]Erreur à l'écoute.\n");
		exit(1);
	}

	// CREATION ET RECEPTION DU FICHIER
	FILE *fp = fopen(argv[1], "wb");
	addr_size = sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
	write_file(new_sock, fp);
	printf("[+]Fichier reçu avec succès.\n");

	// FIN DU PROGRAMME
	return 0;
}

void write_file(int sockfd, FILE *fp){

	// DECLARATION DES VARIABLES
	ssize_t n;
	char buff[MAX_LINE] = {0};

	// ECRITURE DES DONNEES DANS LE FICHIER
	while((n = recv(sockfd, buff, MAX_LINE, 0)) > 0) {
		total =+n;
		if (n == -1){
			perror("[-]Erreur à la réception du fichier.\n");
			exit(1);
		}

		if (fwrite(buff, sizeof(char), n, fp) != n) {
			perror("[-]Erreur à l'écriture du fichier.\n");
			exit(1);
		}
		memset(buff, 0, MAX_LINE);
	}
}
