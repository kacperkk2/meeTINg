#ifndef SERVER_PROTOTYPE_CONNECTIONMANAGER_H
#define SERVER_PROTOTYPE_CONNECTIONMANAGER_H

#define BUFLEN 128

class ConnectionManager {

private:
    int fdmax; // numer najwiekszego deskryptora
    fd_set master; // glowna lista deskryptorow
    fd_set ready; // pomocnicza lista deskryptorow dla selecta
    int listenerfd; // deskryptor gniazda nasluchujacego
    sockaddr_in listeneraddr; // adres nasluchujacego
    char buf; // jednobajtowe komunikaty od watka nadrzednego
    char incomingMessage[BUFLEN]; // bufor na wiadomosci przychodzace
    char completeMessage[BUFLEN]; // bufor do wyslania pelnej wiadomosci zwrotnej klientowi
    int nbytes_rec;
    int processed_bytes;
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

};


#endif //SERVER_PROTOTYPE_CONNECTIONMANAGER_H
