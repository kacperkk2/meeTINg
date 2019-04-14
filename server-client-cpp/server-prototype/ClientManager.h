//
// Created by Tomasz Suchodolski on 14.04.19.
//

#ifndef SERVER_PROTOTYPE_CLIENTMANAGER_H
#define SERVER_PROTOTYPE_CLIENTMANAGER_H


class ClientManager {

private:
    // Disallow creating an instance of this object
    ClientManager() = default;
    static int send_all(int fd, char* buf, int* len);

public:
    static void *handle_client(void* fd);
    static void handle_new_connection(int listenerfd, int &fdmax, fd_set master);

};


#endif //SERVER_PROTOTYPE_CLIENTMANAGER_H
