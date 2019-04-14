//
// Created by Tomasz Suchodolski on 14.04.19.
//

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <cstring>
#include "PackageSizeParser.h"
#include "ClientManager.h"

#define BUFLEN 128
#define PORT 9543
#define BACKLOG 10

using namespace std;

int ClientManager::send_all(int fd, char* buf, int* len)
{
    cout << "~~W FUNKCJI" << endl;
    int total = 0; // ile juz sie udalo wyslac
    int left = *len; // ile jeszcze do wyslania
    int nbytes = 0;

    while(total < *len)
    {
        cout << "~~WYSYLAM" << endl;
        nbytes = send(fd, buf+total, left, 0);
        if(nbytes == -1)
            break;

        total += nbytes;
        left -= nbytes;
    }

    *len = total; // ile udalo sie wyslac faktycznie

    if(nbytes == -1)
        return -1;
    else
        return 0;
}

void *ClientManager::handle_client(void* fd)
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
    sockaddr_in listeneraddr; // adres nasluchujacego

    if((listenerfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    listeneraddr.sin_family = AF_INET;
    listeneraddr.sin_port = htons(PORT);
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
    char incomingMessage[BUFLEN]; // bufor na wiadomosci
    char completeMessage[BUFLEN];
    int nbytes_rec;

    int processed_bytes = 0;

    bool work = true;

    // glowna petla, czyli obsluguj wszystkie deskryptory
    while(work)
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
                    socklen_t addrlength;
                    int clientfd; // deskryptor nowego clienta
                    sockaddr_in clientaddr; // adres klienta
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

                    if(buf == 'x' || buf == 'q')
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

                        if(buf == 'q')
                            work = false;

                        break;
                    }
                }
                    // ktorys klient cos napisal
                else
                {
                    memset(incomingMessage, 0, BUFLEN);
                    memset(completeMessage, 0, BUFLEN);
                    nbytes_rec = recv(i, incomingMessage, sizeof(incomingMessage), 0);
                    // otrzymujemy jakas wiadomosc


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
                        memcpy(completeMessage, incomingMessage, nbytes_rec);
                        processed_bytes = nbytes_rec;
                        cout << "Otrzymalem na poczatku: " << processed_bytes << endl; // --------------------------------------------------------------------

                        while (processed_bytes < 4) {
                            cout << "Mam mniej niz 4 bajty" << endl; // ------------------------------------
                            nbytes_rec = recv(i, incomingMessage, sizeof(incomingMessage), 0);
                            if(nbytes_rec  <= 0) // jesli rozlaczyl sie lub sa bledy, to zamykam jego deskryptor
                            {
                                if (nbytes_rec == 0) // koniec lacznosci
                                    printf("~~ Socket %d hung up \n", i);
                                else
                                    perror("recv");
                            }

                            memcpy(&completeMessage[processed_bytes], incomingMessage, nbytes_rec);
                            processed_bytes += nbytes_rec;
                        }

                        cout << "Przerobilem bytes: " << processed_bytes << endl; // --------------------------------------------------------------------

                        int32_t message_size;
                        char size_to_convert[4];
                        size_to_convert[0] = completeMessage[0];
                        size_to_convert[1] = completeMessage[1];
                        size_to_convert[2] = completeMessage[2];
                        size_to_convert[3] = completeMessage[3];

                        message_size = PackageSizeParser::parse_int_32(size_to_convert);
                        int package_size = message_size + 4;

                        cout << "message_size(bez naglowka): "<< message_size << endl; // --------------------------------------------------------------------
                        cout << "processed_bytes: "<< processed_bytes << endl;
                        cout << "package_size: "<< package_size << endl;

                        if (processed_bytes != package_size) {
                            cout << "Mam za malo, musze dozbierac wiadomosc" << endl;
                            do {
                                nbytes_rec = recv(i, incomingMessage, sizeof(incomingMessage), 0);
                                memcpy(&completeMessage[processed_bytes], incomingMessage, nbytes_rec);
                                processed_bytes += nbytes_rec;
                            } while (processed_bytes < package_size);
                        }

                        cout << "processed_bytes: "<< processed_bytes << endl;
                        cout << "Mam cala wiadomosc, daje ja do klienta" << endl; // --------------------------------------------------------------------

                        // wyslij mu wiadomosc spowrotem
                        if(send_all(i, completeMessage, &processed_bytes) == -1)
                        {
                            perror("send");
                            printf("~~ Sent only %d bytes (error) \n", processed_bytes);
                        }

                        cout << "Wyslalem mu wiadomosc .............. " << endl;
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

void ClientManager::handle_new_connection(int listenerfd, int &fdmax, fd_set master) {
    socklen_t addrlength;
    int clientfd; // deskryptor nowego clienta
    sockaddr_in clientaddr; // adres klienta
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
