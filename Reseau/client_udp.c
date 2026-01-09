#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100
#define PORT 9600

int main(int argc, char *argv[]) {
    //variable du client
    int sockfd;
    struct sockaddr_in serv_addr; //structure adresse
    struct hostent *server; //pointeur
    char buffer[SIZE]; //memoire
    socklen_t serv_len = sizeof(serv_addr); //taille de chaine

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <adresse_serveur>\n", argv[0]);
        return 1;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    if ((server = gethostbyname(argv[1])) == NULL) {
        fprintf(stderr, "Erreur : hôte inconnu %s\n", argv[1]);
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr = *((struct in_addr *)server->h_addr);

    printf("Message à envoyer : ");
    fflush(stdout);
    fgets(buffer, SIZE, stdin); 

    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr*)&serv_addr, serv_len);

    close(sockfd);
    return 0;
}
