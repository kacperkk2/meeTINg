#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include "ConnectionManager.h"
#include "ServerController.h"


using namespace std;



ConnectionManager::ConnectionManager(DataBaseConnection &dbc)
    :dbc(dbc)
{
    FD_ZERO(&master);
    FD_ZERO(&ready);

}

int ConnectionManager::send_all(int fd, char *buf, int *len) {
    cout << buff[0] << buf[4] << buf[5] << buf[11] << buf[12] <<endl;
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

            //obsluga zadania klienta
            sc.selectAction(fd,cli_struct[fd], *this, dbc);

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
    if(read(pipe_fd[0], &buf, 1) == -1)
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
            if(j != pipe_fd[0] && j != pipe_fd[1] && j != listenerfd)
            {
                close(j);
                FD_CLR(j, &master);
            }
        }

        // fdmax ustawiam na najnizsze mozliwe, bo zamknalem wszystkich klientow
        fdmax = pipe_fd[0];
        set_if_higher_fd(listenerfd);

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
    int attempts = 0;

    while(attempts < 20) {
        sleep(2);
        if ((clientfd = accept(listenerfd, (sockaddr*)&clientaddr, &addrlength)) == -1)
        {
            attempts++;
            continue; // na wszelki wypadek nie wychodze jakby sie nie udalo accept
        }
        else
        {
            int flags = fcntl(clientfd, F_GETFL);
            if (flags == -1) {
                attempts++;
                perror("F_GETFL clientfd");
                printf("~~ Connection from %s on socket %d refused. Retrying... \n", inet_ntoa(clientaddr.sin_addr), clientfd);
                close(clientfd);
                continue;
            }
            if (fcntl(clientfd, F_SETFL, flags | O_NONBLOCK) == -1) {
                attempts++;
                perror("F_SETFL clientfd");
                printf("~~ Connection from %s on socket %d refused. Retrying... \n", inet_ntoa(clientaddr.sin_addr), clientfd);
                close(clientfd);
                continue;
            }
            FD_SET(clientfd, &master);
            set_if_higher_fd(clientfd);

            // tworze w mapie miejsce na strukture klienta
            cli_struct[clientfd] = ClientStructure();

            printf("~~ New connection from %s on socket %d \n", inet_ntoa(clientaddr.sin_addr), clientfd);
            return;
        }
    }
    perror("handle_new_connection() failed");
    exit(EXIT_FAILURE);
}


void ConnectionManager::create_listener(int PORT, int BACKLOG) {
    // TODO mozna dodac tak samo ograniczona ilosc prob stworzenia socketu nasluchujacego (tak jak w handle_new_connection), ale to do ustalenia
    bool listener_set = false;

    listeneraddr.sin_family = AF_INET;
    listeneraddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &listeneraddr.sin_addr);

     while (!listener_set) {
         sleep(2);

        if((listenerfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("socket");
            continue;
        }

        int flags = fcntl(listenerfd, F_GETFL);
        if (flags == -1) {
            perror("F_GETFL listenerfd");
            close(listenerfd);
            continue;
        }
        if (fcntl(listenerfd, F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("F_SETFL listenerfd");
            close(listenerfd);
            continue;
        }

        if (bind(listenerfd, (sockaddr*)&listeneraddr, sizeof(listeneraddr)) == -1)
        {
            perror("bind");
            close(listenerfd);
            continue;
        }

        if (listen(listenerfd, BACKLOG) == -1)
        {
            perror("listen");
            close(listenerfd);
            continue;
        }

        FD_SET(listenerfd, &master);
        set_if_higher_fd(listenerfd);
        listener_set = true;
    }
}

void ConnectionManager::manage_connections(int BACKLOG, void* args) {

    int* casted_args = (int*) (intptr_t) args;
    pipe_fd[0] = casted_args[0];
    pipe_fd[1] = casted_args[1];

    FD_SET(pipe_fd[0], &master); // dodaje read pipe deskryptor do listy moich deskryptorow
    fdmax = pipe_fd[0];

    struct timeval tv;

    create_listener(casted_args[2], BACKLOG);

    // glowna petla, czyli obsluguj wszystkie deskryptory
    while(work)
    {
        tv = {2, 0};
        ready = master; // przekopiuj oryginalny set, bo select zmienia seta
        errors = master;
        // TODO sprawdzenie, czy nie wywalilo klienta - errors powinien w jakis sposob zwracac deskryptor, gdzie wystapil blad

        if(select(fdmax+1, &ready, (fd_set *)0, &errors, &tv) == -1) {
            perror("select");
            continue;
        }

        // patrze ktory deskryptor obudzil selecta
        for(int i = 3; i < fdmax+1; i++)
        {
            if(FD_ISSET(i, &ready)) // sprawdzanie ktory deskryptor
            {
                if(i == listenerfd) { // to nasluchiwacz, wiec przyszlo nowe polaczenie od klienta
                    handle_new_connection();
                }
                else if(i == pipe_fd[0]) { // watek nadrzedny cos chce
                    if (handle_console_request() == 1) break;
                }
                else { // ktorys klient cos napisal
                    handle_client_request(i);

                }
            }
        }
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(listenerfd);
}

void ConnectionManager::set_if_higher_fd(int fdnew) {
    if(fdnew > fdmax) // jesli ten numer jest wiekszy od aktualnego to zapamietuje
        fdmax = fdnew;
}
