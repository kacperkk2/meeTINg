#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "ConnectionManager.h"


using namespace std;

ConnectionManager::ConnectionManager() {
    FD_ZERO(&master);
    FD_ZERO(&ready);
}

int ConnectionManager::send_all(int fd, char *buf, int *len) {
    int total = 0; // ile juz sie udalo wyslac
    int left = *len; // ile jeszcze do wyslania
    int nbytes = 0;

    while(total < *len)
    {
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

void ConnectionManager::handle_client_request(int fd) {

    char* incomingMessage = new char[cli_struct[fd].get_bytes_needed()];

    // otrzymujemy jakas wiadomosc
    nbytes_rec = recv(fd, incomingMessage, cli_struct[fd].get_bytes_needed(), 0);

    if(nbytes_rec  <= 0) // jesli rozlaczyl sie lub sa bledy, to zamykam jego deskryptor
    {
        if(nbytes_rec  == 0) // koniec lacznosci
            printf("~~ Socket %d hung up \n", fd);
        else
            perror("recv");

        close(fd);
        FD_CLR(fd, &master);

        // jesli ten klient ktory sie rozlaczyl to byl najwiekszy deskryptor, to teraz najwiekszy bedzie o jeden mniej
        if(fd == fdmax)
            fdmax --;

        // usuwam miejsce w mapie
        cli_struct.erase(fd);
    }
    else // odebrano wiadomosc
    {
        cout << "Odebrano bajtow: "<< nbytes_rec << endl;
        cli_struct[fd].set_part_message(incomingMessage, nbytes_rec);
        delete [] incomingMessage;

        //zostawiam stare rozwiazanie bo jak byly by watki to nwm czy tamto by dzialalo, rozkmina
//        if (cli_struct[fd].whole_package_size != -1 && cli_struct[fd].get_bytes_received() >= cli_struct[fd].whole_package_size) {
        // jesli odebralismy caly pakiet to wyslij mu wiadomosc spowrotem
        if (cli_struct[fd].get_bytes_needed() <= 0) {
            cout << "Mam juz cala wiadomosc, moge ja zwrocic" << endl;

            int bytes = cli_struct[fd].get_whole_package_size();
            if (send_all(fd, cli_struct[fd].get_buffer_message(), &bytes) == -1) {
                perror("send");
                printf("~~ Sent only %d bytes (error) \n", bytes);
            }

            // przywracam domyslne ustawienia, bo wyslalem, zostaje czyste na nastepny raz
            cli_struct[fd].dealloc();
            cli_struct[fd].init();
        }
        else
            cout << "Jeszcze nie mam calej wiadomosci" << endl;
    }
}

int ConnectionManager::handle_console_request() {
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

                // fdmax ustawiam na najnizsze mozliwe, bo zamknalem wszystkich klientow
                fdmax = readfd_pipe[0];
                set_if_higher_fd(listenerfd);
            }
        }

        if(buf == 'q')
            work = false;

        return 1;
    }
    return 0;
}

void ConnectionManager::handle_new_connection() {
    socklen_t addrlength;
    int clientfd; // deskryptor nowego clienta
    sockaddr_in clientaddr; // adres klienta
    addrlength = sizeof(clientaddr);

    if ((clientfd = accept(listenerfd, (sockaddr*)&clientaddr, &addrlength)) == -1)
        perror("accept"); // na wszelki wypadek nie wychodze jakby sie nie udalo accept
    else
    {
        FD_SET(clientfd, &master);
        set_if_higher_fd(clientfd);

        // tworze w mapie miejsce na strukture klienta
        cli_struct[clientfd] = ClientStructure();

        printf("~~ New connection from %s on socket %d \n", inet_ntoa(clientaddr.sin_addr), clientfd);
    }
}

void ConnectionManager::create_listener(int PORT, int BACKLOG) {
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
    set_if_higher_fd(listenerfd);
}

void ConnectionManager::manage_connections(int PORT, int BACKLOG, void* fd) {

    readfd_pipe = (int*) (intptr_t) fd;
    FD_SET(readfd_pipe[0], &master); // dodaje read pipe deskryptor do listy moich deskryptorow
    fdmax = readfd_pipe[0];

    create_listener(PORT, BACKLOG);

    // glowna petla, czyli obsluguj wszystkie deskryptory
    while(work)
    {
        ready = master; // przekopiuj oryginalny set, bo select zmienia seta

        if(select(fdmax+1, &ready, (fd_set *)0, (fd_set *)0, 0) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // patrze ktory deskryptor obudzil selecta
        for(int i = 3; i < fdmax+1; i++)
        {
            if(FD_ISSET(i, &ready)) // sprawdzanie ktory deskryptor
            {
                if(i == listenerfd) { // to nasluchiwacz, wiec przyszlo nowe polaczenie od klienta
                    handle_new_connection();
                }
                else if(i == readfd_pipe[0]) { // watek nadrzedny cos chce
                    if (handle_console_request() == 1) break;
                }
                else { // ktorys klient cos napisal
                    handle_client_request(i);
                }
            }
        }
    }

    close(readfd_pipe[0]);
    close(readfd_pipe[1]);
    close(listenerfd);
}

void ConnectionManager::set_if_higher_fd(int fdnew) {
    if(fdnew > fdmax) // jesli ten numer jest wiekszy od aktualnego to zapamietuje
        fdmax = fdnew;
}
