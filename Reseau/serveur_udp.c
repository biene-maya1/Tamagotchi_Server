#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 9600
#define BUFSIZE 256

int main(int argc, char *argv[]){
    int sockfd;                            // descripteur de socket
    struct sockaddr_in serv_addr;          // adresse locale du serveur
    struct sockaddr_in cli_addr;           // adresse du client
    socklen_t cli_len = sizeof(cli_addr);  // taille adresse client
    char buffer[BUFSIZE];

    // Création du socket UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Attachement du socket au port
    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror("bind");
        return 1;
    }

    printf("ecoute sur le port %d...\n", PORT);

    while(1){
        // Attendre un message du client
        ssize_t n = recvfrom(sockfd, buffer, BUFSIZE-1, 0,
                             (struct sockaddr*)&cli_addr, &cli_len);
        if(n < 0){
            perror("recvfrom");
            continue;
        }

        buffer[n] = '\0';  // terminer la chaîne reçue
        printf("Message reçu : %s\n", buffer);

        // Réponse simple
        const char *response = "Message reçu";
        sendto(sockfd, response, strlen(response), 0,
               (struct sockaddr*)&cli_addr, cli_len);
    }

    close(sockfd);
    return 0;
}

