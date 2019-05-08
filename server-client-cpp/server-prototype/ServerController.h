//
// Created by michal on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_SERVERCONTROLLER_H
#define SERVER_PROTOTYPE_SERVERCONTROLLER_H

#include <string>
#include "DataBaseConnection.h"
#include "ClientStructure.h"


using namespace std;

class ConnectionManager;
class DataBaseConnection;
class ServerController {



public:

    ServerController();
    static void selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc);
    static string logonData(string message, ConnectionManager &cm, DataBaseConnection &dbc);
    static void sendResponse(int fd, char* response, int responseSize, ConnectionManager &cm);
};


#endif //SERVER_PROTOTYPE_SERVERCONTROLLER_H
