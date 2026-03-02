#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h> // Potrzebne do wątków

// Wątek, który działa w tle i CZYTA to, co przysyła serwer
void *odbieraj_wiadomosci(void *socket_desc) {
    int sock = *(int*)socket_desc;
    char buffer[512];
    
    while(1) {
        memset(buffer, 0, 512);
        if (recv(sock, buffer, 511, 0) <= 0) {
            printf("\nRozłączono z serwerem.\n");
            exit(0);
        }
        printf("%s", buffer);
        fflush(stdout); 
    }
    return NULL;
}

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[256];
    pthread_t thread_id;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Błąd połączenia. Czy serwer jest włączony?\n");
        return 1;
    }

    // Uruchamiamy wątek w tle, który nasłuchuje serwera
    pthread_create(&thread_id, NULL, odbieraj_wiadomosci, (void*)&sock);

    // Główna pętla programu PISZE do serwera
    while(1) {
        memset(buffer, 0, 256);
        fgets(buffer, 256, stdin); 
        if (strcmp(buffer, "-1\n") == 0) {
            break;
        }
        
        send(sock, buffer, strlen(buffer), 0);
    }

    close(sock);
    return 0;
}