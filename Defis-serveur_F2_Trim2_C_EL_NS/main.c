#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int socklen_t;

#define PORT 23

//serveur
int main()
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);

    // Socket et contexte d'adressage du serveur
    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t recsize = sizeof(sin);

    // Socket et contexte d'adressage du client
    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t crecsize = sizeof(csin);

    int sock_err;

    int score = 0;
    char reponse[3] = "";

    char enigmes[10][1000] =
    {
        "Enigme 1 : \nHier soir, je rentre tard avec des petites idees derriere la tete, et m'empresse d'en faire part a ma copine. \nElle me repond : Viens on va se brosser les dents avant ! \nJe commence a la pousser sur le lit, et lui repond que ce n'est pas important,  et qu'on verra ca apres ! \nQu'a t'elle pue repondre ? \n\n1- Tu pourrait tuer un vampire avec ton haleine tellement tu sens l'ail \n\n2- Ah non mais c'est juste que c'est pas possible la. J'ai l'impression d'avoir un vieux bouquetin qui vient de passer  10 jours a se nourrir dans un champ d'ail en face de moi !* \n\n3- Tu as deja croquer de l'ail ? j'ai l'impression de le faire la, vue ton haleine \n\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 2 : \nDepuis plusieurs mois, j'ai de gros soucis, le soldat ne se met plus du tout aux garde-a-vous.\nHier soir, dans le lit avec ma copine, elle lit les NSF. \nA ma solitude, quand elle a lance calmement : \n\n\n1- J'en suis au point ou j'aimerai bien que ces trucs la m'arrivent...*\n2- Je pourrai clairement en ecrire une sur notre situation actuelle\n3- Quand je les lits, je plain ceux a qui cela arrive puis je pense a nous...\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 3 : \nCelibataire depuis beaucoup trop longtemps, ce matin, en ouvrant youtube, mes suggestions de videos etaient :\nEtre Celibataire - MisterV\nLa Masturbation - Norman\nLa premiere fois - Palmashow\nQu'est ce que je doit en penser ? \n\n\n1- Donc meme youtube me rabaisse...\n2- Youtube me connait trop bien, ca en devient flippant...\n3- Je crois que meme Google se fou de ma gueule.* \nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 4 : \nHier, j'ai retrouve un jeu de carte dans notre chambre.\nD'humeur caliente, je propose un strip poker a ma copine.\nSans un regard, elle m'a repondu froidement :\n\n\n1- Le but quand on joue a un jeu, c'est de gagner quelque chose et c'est pas comme si tu avait quelque chose de bien a m'offrir...\n2- Tu as vu qu'on a aussi le solitaire en jeu ?*\n3- Seulement si apres on joue a qui a choper des morpions\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 5 : \nIl y a quelques jours, ma copine (qui s'appelle Camille) vient dormir chez moi.\nElle etait en train de s'occuper de moi, quand mon pere appel.\nJe decroche, mais elle continue car elle a le sentiment d'etre discrete.\nA la punchline mythique de mon pere :\n\n\n1- Elle s'occupe donc de toi si mal pour que tu reponde au telephone en meme temps ?\n2- Tu diras a Camille de me confirmer si vous venez manger a la maison ce weekend car apparament elle est occupee la.\n3- Tiens, tu me passeras Camille quand elle n'aura plus la bouche pleine s'il te plait.*\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 6 : \nHier soir, ma copine est venu dormir chez moi.\nElle n'a jamais reussit a le faire durcir malgre tous ses efforts.\nAu dejeuner ce matin, mon pere lui lance :\nAlors, le soldat a bien dormi ? \nA la reponse de ma copine :\n\n\n1- C'est le cas de le dire...\n2- Oula oui, le soldat etait carrement dans le coma.*\n3- Comment dire, il faudrait deja que le soldat se soit reveiller...\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 7 : \nHier en boite, je me rapproche d'une fille.\nBien alcoolise, et apres un long colle-serre, elle me chuchote a l'oreille :\nEn ce moment j'ai carrement faim !!\nAutant vous dire que la nuit s'annoncait torride.\nHeureux, je lui propose donc de partir. A ma tete quand elle m'a lache 2h plus tard, apres qu'on ai mange un enorme tacos, et qu'elle m'ait lance :\n\n\n1- Enfin ! merci, j'ai cru que j'allais mourir de faim\n2- Ahhh bordel ! Ca fait du bien ! Hein ?*\n3- Apres une boite de nuit, ca c'est ce que j'appel se faire plaisir !!\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 8 : \nJ'ai quitte ma copine il y a quelques semaines parce qu'elle n'avait absolument jamais envie de s'amuser (on ne parle pas de jeux de societe, vous avez compris).\nAujourd'hui je l'ai croisee sur une applie de rencontre.\nSa description ?\n\n\n1- Ici pour rattraper 4 mois de sexe plus que minable.*\n2- Si tu ne sais pas t'en servir, me demande pas de jouer avec...\n3- Je cherche juste quelqu'un capable de m'enmener au 7�me ciel.\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 9 : \nUn matin, alors que je partais en vacances avec ma copine et ses parents, on est pris d'une pulsion hyper forte.\nComme est l'un a cote de l'autre a l'arriere de la voiture, on met un manteau sur nous et on se touche un peu.\nA ce moment de malaise mythique quand sa mere a lancee :\n\n\n1- Hummm la bonne odeur de fruit de mer...\n2- J'ai comme une envie de manger des moules. Arretons-nous pour aller en manger dans un restaurant.\n3- Oh ca sent la crevette dans ce coin ! Arretons nous manger bientot, j'ai envie de fruit de mer maintenant !*\nEntrer le nombre correspondant a la situation qui c'est reellement passe : ",
        "Enigme 10 : \nHier je vais donner mon sang, accompagne de ma copine.\nUne fois le don effectue, l'infirmier me dit d'eviter les efforts violents (sport, etc) pendant 24 heures.\nPour faire de l'humour je demande si �a inclut le sport de chambre.La, ma copine s'exclame :\n\n\n1- Si seulement tu en etait capable de t'epuiser a la tache...\n2- T'inquietes pas cheri, de ce cote-la tu risques pas de t'epuiser !*\n3- Le monsieur a parler d'effort violent ! On ne peut pas en dire autant de toi au lit...\nEntrer le nombre correspondant a la situation qui c'est reellement passe : "
    };

    char soluces[10][1] = {"2","1","3","2","3","2","2","1","3","2"};

    char intro[300] = "Bonjour ! \nBienvenue dans le journal intime d'un looser. \nVous aurez a choisir la situation qui lui ai arrive \nChaque bonne reponse vous amenera a la situation suivante \n\n\nVoici la premiere situation : \nAppuyer sur entrer pour afficher l'enigme.";
    //char fin[300] = "Vous etes arrive au bout du journal intime.\nOn est d'accord que ce pauvre homme en a vecu des mauvaises situations...\nCombien de reponses correcte avez-vous ?\nVoici votre score : %d\nAppuyer sur entree pour quitter.";
    char succes[80] = "Bravo, vous avez trouver la bonne reponse ! +1 points\n\n\n";
    char echec[80] = "Dommage ! Ce n'est pas ce qu'il s'est passé !\n\n\n";
    //char separateur[100] = "____________________________________________________________\n\n";



    // Création d'une socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock != INVALID_SOCKET) // Si la socket est valide
    {
        printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

        // Configuration
        sin.sin_addr.s_addr = htonl(INADDR_ANY);  // Adresse IP automatique
        sin.sin_family = AF_INET;                 // Protocole familial (IP)
        sin.sin_port = htons(PORT);               // Listage du port
        sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

        if(sock_err != SOCKET_ERROR) // Si la socket fonctionne
        {
            // Démarrage du listage (mode server)
            sock_err = listen(sock, 5);
            printf("Listage du port %d...\n", PORT);

            // Si la socket fonctionne
            if(sock_err != SOCKET_ERROR)
            {
                printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);
                csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
            }
            else
                perror("listen");

            sock_err = send(csock, intro, sizeof(intro), 0);

            for (int i = 0; i < 10; i++)
            {
                sock_err = send(csock, enigmes[i], sizeof(enigmes[i]), 0);

                if(recv(sock, reponse, sizeof(reponse), 0) != SOCKET_ERROR)
                {
                    if(reponse == soluces[i])
                    {
                        sock_err = send(csock, succes, sizeof(succes), 0);
                        score++;
                    }
                    else
                        sock_err = send(csock, echec, sizeof(echec), 0);
                }
            }

            send(sock, &score, sizeof(score), 0);

            /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
            shutdown(csock, 2);
    }
    else
        perror("bind");

    // Fermeture de la socket client et de la socket serveur
    printf("Fermeture de la socket client\n");
    closesocket(csock);
    printf("Fermeture de la socket serveur\n");
    closesocket(sock);
    printf("Fermeture du serveur termin�e\n");
    }
    else
        perror("socket");

    WSACleanup();

    return EXIT_SUCCESS;
}
