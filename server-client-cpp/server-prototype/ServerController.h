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


    //DataBaseConnection dbc;


    ServerController();
    void selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc);
    string logonData(string message, ConnectionManager &cm, DataBaseConnection &dbc);
    void sendResponse(int fd, string response, int responseSize, ConnectionManager &cm);
};


#endif //SERVER_PROTOTYPE_SERVERCONTROLLER_H
