//
// Created by michal on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_SERVERCONTROLLER_H
#define SERVER_PROTOTYPE_SERVERCONTROLLER_H

#include <string>
#include "DataBaseConnection.h"
#include <ClientStructure.h>


using namespace std;

class ServerController {



public:
    DataBaseConnection dbc = DataBaseConnection("admin", "admin");
    ServerController();
    void selectAction(int fd, ClientStructure client);
    string logonData(string message);
};


#endif //SERVER_PROTOTYPE_SERVERCONTROLLER_H
