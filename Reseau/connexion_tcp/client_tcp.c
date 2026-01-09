// client_tcp.c - Tamagotchi !
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

static void die(const char *msg) { perror(msg); exit(1); }

static void read_available(int fd) {
    char buf[512];

    while (1) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd, &set);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 200000;

        int r = select(fd + 1, &set, NULL, NULL, &tv);
        if (r <= 0) return; 

        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        if (n <= 0) {
            printf("Deconnecte.\n");
            exit(0);
        }
        buf[n] = 0;
        printf("%s", buf);
        fflush(stdout);
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        return 1;
    }

    const char* host = argv[1];
    int port = atoi(argv[2]);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) die("socket");

    struct hostent* he = gethostbyname(host);
    if (!he) { fprintf(stderr, "Host introuvable\n"); return 1; }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((unsigned short)port);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) die("connect");
    read_available(fd);

    char line[256];
    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) break;
        if (write(fd, line, strlen(line)) < 0) die("write");
        read_available(fd);
    }

    close(fd);
    return 0;
}


