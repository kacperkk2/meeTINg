#ifndef SERVER_PROTOTYPE_CONNECTIONMANAGER_H
#define SERVER_PROTOTYPE_CONNECTIONMANAGER_H

#include <map>
#include "ClientStructure.h"


class ConnectionManager {

private:
    std::map<int, ClientStructure> cli_struct; // mapuje deskryptor klienta -> struktura klienta, w niej gromadzone sa otrzymane bajty
    int fdmax; // numer najwiekszego deskryptora
    fd_set master; // glowna lista deskryptorow
    fd_set ready; // pomocnicza lista deskryptorow dla selecta
    int listenerfd; // deskryptor gniazda nasluchujacego
    sockaddr_in listeneraddr; // adres nasluchujacego
    char buf; // jednobajtowe komunikaty od watka nadrzednego
    int nbytes_rec;
    bool work = true;
    int *readfd_pipe;

public:
    ConnectionManager();
    void manage_connections(int, int, void*);
    void create_listener(int, int);
    void handle_new_connection();
    int handle_console_request();
    void handle_client_request(int);
    int send_all(int, char*, int*);
    void set_if_higher_fd(int);

};


#endif //SERVER_PROTOTYPE_CONNECTIONMANAGER_H
