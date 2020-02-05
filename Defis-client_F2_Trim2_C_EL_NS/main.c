#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int socklen_t;

#define PORT 23

//client
int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);

    SOCKET csock;
    SOCKET sock;
    SOCKADDR_IN sin;

    int sock_err;
    int score;

    char enigmes[10][1000] = {"","","","","","","","","",""};

    char intro[300] = "";
    char succes[80] = "";
    char echec[80] = "";
    char separateur[100] = "____________________________________________________________\n\n";

    char reponse[3] = "";

    // Création de la socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Configuration de la connexion
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    // Si le client arrive à se connecter
    if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            printf("Connexion a %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            // Si l'on reçoit des informations : on les affiche à l'écran
            if(recv(sock, intro, sizeof(intro), 0) != SOCKET_ERROR)
                printf("%s\n", intro);

            for (int i = 0; i < 10; i++)
            {
                if(recv(sock, enigmes[i], sizeof(enigmes[i]), 0) != SOCKET_ERROR)
                    printf("%s\n", enigmes[i]);
                scanf("%c", &reponse);
                fflush(stdin);
                sock_err = send(csock, reponse, sizeof(reponse), 0);

                if(recv(sock, succes, sizeof(succes), 0) != SOCKET_ERROR)
                    printf("%s\n", succes);
                else if(recv(sock, echec, sizeof(echec), 0) != SOCKET_ERROR)
                    printf("%s\n", echec);

                printf(separateur);
            }

            if(recv(sock, &score, sizeof(score), 0) != SOCKET_ERROR)
                printf("Vous etes arrive au bout du journal intime.\nOn est d'accord que ce pauvre homme en a vecu des mauvaises situations...\nCombien de reponses correcte avez-vous ?\nVoici votre score : %d\nAppuyer sur entree pour quitter.", &score);

        }
    else
        printf("Impossible de se connecter\n");

    getchar();
    // On ferme la socket précédemment ouverte
    closesocket(sock);

    getchar();

    WSACleanup();

    return EXIT_SUCCESS;
}
