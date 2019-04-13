#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <sys/file.h>
#include <cstdlib>
#include <algorithm>
#include <vector>

extern int errno;

using namespace std;

#define BUFLEN 20
#define MYPORT 9543
#define BACKLOG 10


//char BUF_MSG[BUFLEN];

void *handle_client(void* fd)
{
    int fdmax; // numer najwiekszego deskryptora
    fd_set master; // glowna lista deskryptorow
    fd_set ready; // pomocnicza lista deskryptorow dla selecta
    FD_ZERO(&master);
    FD_ZERO(&ready);

    // gawkowski mowil zeby sprawdzic deskryptor ktory sie dostaje ale czy to potrzebne? bo pipe() to sprawdza
    int *readfd_pipe = (int*) (intptr_t) fd;
    FD_SET(readfd_pipe[0], &master); // dodaje read pipe deskryptor do listy moich deskryptorow
    FD_SET(readfd_pipe[1], &master); // dodaje write pipe deskryptor do listy moich deskryptorow

    fdmax = readfd_pipe[0] > readfd_pipe[1] ? readfd_pipe[0] : readfd_pipe[1]; // poki co ten jest najwiekszy


    int listenerfd; // deskryptor gniazda nasluchujacego
    int clientfd; // deskryptor nowego clienta
    sockaddr_in listeneraddr; // adres nasluchujacego
    sockaddr_in clientaddr; // adres klienta

    if((listenerfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    listeneraddr.sin_family = AF_INET;
    listeneraddr.sin_port = htons(MYPORT);
    inet_pton(AF_INET, "0.0.0.0", &listeneraddr.sin_addr);
    if (bind(listenerfd, (sockaddr*)&listeneraddr, sizeof(listeneraddr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(listenerfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    FD_SET(listenerfd, &master);
    if(listenerfd > fdmax) // jesli ten numer jest wiekszy to zapamietuje
        fdmax = listenerfd;

    char buf; // jedno bajtowe komunikaty od watka nadrzednego
    char message[BUFLEN]; // bufor na wiadomosci
    socklen_t addrlength;
    int nbytes_rec;

    // glowna petla, czyli obsluguj wszystkie deskryptory
    while(1)
    {
        ready = master; // przekopiuj oryginalny set, bo select zmienia seta

        if(select(fdmax+1, &ready, (fd_set *)0, (fd_set *)0, 0) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // patrze ktory desktryptor obudzil selecta
        for(int i = 3; i < fdmax+1; i++)
        {
            if(FD_ISSET(i, &ready))
            {
                // to nasluchiwacz, wiec przyszlo nowe polaczenie od klienta
                if(i == listenerfd)
                {
                    addrlength = sizeof(clientaddr);
                    if ((clientfd = accept(listenerfd, (sockaddr*)&clientaddr, &addrlength)) == -1)
                        perror("accept"); // na wszelki wypadek nie wychodze jakby sie nie udalo accept
                    else
                    {
                        FD_SET(clientfd, &master);
                        if(clientfd > fdmax) // jesli ten numer jest wiekszy to zapamietuje
                            fdmax = clientfd;

                        printf("~~ New connection from %s on socket %d \n", inet_ntoa(clientaddr.sin_addr), clientfd);
                    }
                }
                // watek nadrzedny cos chce
                else if(i == readfd_pipe[0])
                {
                    if(read(readfd_pipe[0], &buf, 1) == -1)
                    {
                        perror("read_readfd_pipe");
                        exit(EXIT_FAILURE);
                    }

                    if(buf == 'x')
                    {
                        // zamykam polaczenia
                        for(int j = 3; j < fdmax+1; j++)
                        {
                            // nie zamykam pipe do lacznosci z watkiem i swojego socketa nasluchujacego
                            if(j != readfd_pipe[0] && j != readfd_pipe[1] && j != listenerfd)
                            {
                                close(j);
                                FD_CLR(j, &master);
                            }
                        }
                        break;
                    }
                }
                // ktorys klient cos napisal
                else
                {
                    memset(message, 0, BUFLEN);
                    nbytes_rec = recv(i, message, sizeof(message), 0);
                    cout << "klient napisal wiadomosc" ;
                    if(nbytes_rec  <= 0) // jesli rozlaczyl sie lub sa bledy, to zamykam jego deskryptor
                    {
                        if(nbytes_rec  == 0) // koniec lacznosci
                            printf("~~ Socket %d hung up \n", i);
                        else
                            perror("recv");

                        close(i);
                        FD_CLR(i, &master);
                    }
                    else // odebrano wiadomosc
                    {
                        // wyslij mu wiadomosc spowrotem
                        if(send(i, message, nbytes_rec, 0) == -1)
                            perror("send");
                    }
                }
            } // sprawdzanie ktory deskryptor
        } // glowna petla

    }

    close(readfd_pipe[0]);
    close(readfd_pipe[1]);
    close(listenerfd);
    return 0;
}


int main()
{
    int pipefd[2];

    // uzyskanie 2 deskryptorow pipe, [1] do pisania, [0] do czytania
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // utworz nowy watek i przekaz mu deskryptor do pipe do read
    pthread_t thread_id;
    if(pthread_create(&thread_id, NULL, handle_client, (void *) (intptr_t) &pipefd) < 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    int writefd = pipefd[1];

    while(1)
    {
        int choice;
        do
        {
            cout << "---- KONSOLA ADMINA ----"<<endl;
            cout << "1. Zamknij wszystkie polaczenia (wysyla komunikat x)"<<endl;
            cout << "2. Wyslij inny komunikat (wysyla komunikat o)"<<endl;

            cout <<endl<< "Wybierz opcje: ";
            cin >> choice;
        } while(choice < 1 || choice > 2);

        char message;
        switch(choice)
        {
        case 1:
            message = 'x';
            break;
        case 2:
            message = 'o';
            break;
        default:
            message = 'd';
            break;
        }

        if(write(writefd, &message, sizeof(message)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    close(writefd);
    return 0;
}
