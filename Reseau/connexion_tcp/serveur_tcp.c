// serveur_tcp - Tamagotchi !
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void die(const char *msg) { perror(msg); exit(1); }

static int clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

typedef struct {
    int hunger;    
    int energy;   
    int happiness;  
    time_t last_tick;
} Pet;

static void tick(Pet *p) {
    time_t now = time(NULL);
    int dt = (int)(now - p->last_tick);
    if (dt <= 0) return;

    int steps = dt / 3;
    if (steps <= 0) return;

    p->hunger     = clamp(p->hunger + 2*steps, 0, 100);
    p->energy     = clamp(p->energy - 2*steps, 0, 100);
    p->happiness  = clamp(p->happiness - 1*steps, 0, 100);

    p->last_tick = now;
}
//stats du tamagotchi
static void send_stat(int cfd, Pet *p) {
    char out[256];
    snprintf(out, sizeof(out),
             "hunger=%d energy=%d happiness=%d\n",
             p->hunger, p->energy, p->happiness);
    write(cfd, out, strlen(out));
}
//faire attention quil ne soit pas trop fatigué
static int is_dead(Pet *p) {
    return (p->hunger >= 100 && p->energy <= 0);
}

int main(void) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) die("socket");

    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9600);

    if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) die("bind");
    if (listen(sfd, 4) < 0) die("listen");

    printf("Tamagotchi server 9600:\n");

    while (1) {
        int cfd = accept(sfd, NULL, NULL);
        if (cfd < 0) die("accept");

        Pet pet = { .hunger = 30, .energy = 70, .happiness = 60, .last_tick = time(NULL) };

        const char *hello =
            "WELCOME HOME !\n"
            "feed | play | sleep | status | q\n";
        write(cfd, hello, strlen(hello));
        send_stat(cfd, &pet);

        char buf[256];
        while (1) {
            ssize_t n = read(cfd, buf, sizeof(buf)-1);
            if (n <= 0) break;
            buf[n] = '\0';
            buf[strcspn(buf, "\r\n")] = 0;

            tick(&pet);
            if (strcmp(buf, "status") == 0) {
                send_stat(cfd, &pet);
            }
            else if (strcmp(buf, "feed") == 0) {
                pet.hunger = clamp(pet.hunger - 25, 0, 100);
                pet.energy = clamp(pet.energy + 5, 0, 100);
                write(cfd, "Miam! \n", strlen("Miam! \n"));
                send_stat(cfd, &pet);
            }
            else if (strcmp(buf, "play") == 0) {
                pet.happiness = clamp(pet.happiness + 20, 0, 100);
                pet.energy    = clamp(pet.energy - 15, 0, 100);
                pet.hunger    = clamp(pet.hunger + 10, 0, 100);
                const char *msg = "let's gooo\n";
                write(cfd, msg, strlen(msg));
                send_stat(cfd, &pet);
            }
            else if (strcmp(buf, "sleep") == 0) {
                pet.energy = clamp(pet.energy + 30, 0, 100);
                pet.hunger = clamp(pet.hunger + 10, 0, 100);
                write(cfd, "zz..\n", strlen("zz.. \n"));
                send_stat(cfd, &pet);
            }
            else if (strcmp(buf, "q") == 0) {
                write(cfd, "Bye !\n", 5);
                break;
            }
            else {
                const char *msg = "commande inconnue\n";
                write(cfd, msg, strlen(msg));
                send_stat(cfd, &pet);
            }

            if (is_dead(&pet)) {
                const char *msg = "oh oh.. no more energie :/ \n";
                write(cfd, msg, strlen(msg));
                break;
            }
        }

        close(cfd);
        printf("Client disconnected.\n");
    }

    close(sfd);
    return 0;
}

