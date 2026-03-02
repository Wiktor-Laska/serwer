#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <poll.h> 

#define MAX_PLAYERS 4
// struktura całego servera
typedef struct {
    int listenfd, connfd;
    struct sockaddr_in serv_addr; 
    struct pollfd fds[MAX_PLAYERS + 1];
    

    int points[MAX_PLAYERS]; 
    int ready[MAX_PLAYERS];
    int num_players;
} Server;
// inicjalizacja serwera
void init(Server* ms) {
    memset(ms, 0, sizeof(Server));
    
    ms->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ms->serv_addr.sin_family = AF_INET;
    ms->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ms->serv_addr.sin_port = htons(5000); 
    
    bind(ms->listenfd, (struct sockaddr*)&ms->serv_addr, sizeof(ms->serv_addr)); 
    listen(ms->listenfd, 10); 

    ms->fds[0].fd = ms->listenfd;
    ms->fds[0].events = POLLIN;
}
// działanie lobby
void lobby(Server* serv) {
    for(;;) {
        poll(serv->fds, serv->num_players + 1, -1);
        
        // przyjmowanie zgłoszeni(fds[0] nasza poczekalnia dla nowych graczy którzy są później przypisywani od 1 do maks 4)
        if((serv->fds[0].revents & POLLIN) && serv->num_players < MAX_PLAYERS) {
            int new_sock = accept(serv->listenfd, NULL, NULL);
            
            serv->num_players++;
            serv->fds[serv->num_players].fd = new_sock;
            serv->fds[serv->num_players].events = POLLIN;
            serv->points[serv->num_players - 1] = 0;
            serv->ready[serv->num_players - 1] = 0;
            
            char msg[256];
            sprintf(msg, "=== LOBBY ===\nDolaczyles jako Gracz %d.\nWpisz '1', gdy bedziesz gotowy do gry!\n", serv->num_players);
            send(new_sock, msg, strlen(msg), 0);
            
            printf("Gracz %d dolaczyl do Lobby.\n", serv->num_players);
        }

        //sprawdzanie gotowości graczy
        for(int i=1;i<=serv->num_players;i++){
            if (serv->fds[i].revents & POLLIN) {
                char buf[256] = {0};
                int r = recv(serv->fds[i].fd, buf, 255, 0);
                if (r > 0) {
                    if (strncmp(buf, "1", 1) == 0 &&serv->ready[i - 1] == 0) {
                        serv->ready[i - 1] = 1; 
                        char msg[100];
                        sprintf(msg, "-> Gracz %d kliknal READY!\n", i);
                        printf("%s", msg);
                        for (int j = 1; j <= serv->num_players; j++) send(serv->fds[j].fd, msg, strlen(msg), 0);
                    }
                }
            }
        }
        //uruchomienie gry
        if (serv->num_players>=2){
            int all_ready=1;
            for(int i=0;i<serv->num_players;i++){
                if(!serv->ready[i])
                    all_ready=0;
            }
            if(all_ready){
                printf("Wszyscy gotowi\n");
                break;
            }
        }

    }
}
void game(Server* serv){

}
int main() {
    Server main_server;
    
    init(&main_server);
    printf("Serwer uruchomiony. Czekam na graczy na porcie 5000...\n");
    lobby(&main_server);
    game(&main_server);
    return 0;
}