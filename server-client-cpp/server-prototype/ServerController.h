//
// Created by michal on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_SERVERCONTROLLER_H
#define SERVER_PROTOTYPE_SERVERCONTROLLER_H

#include <string>
#include "DataBaseConnection.h"
#include "ClientStructure.h"
#include "nlohmann/json.hpp"


using namespace std;
using namespace nlohmann;

class ConnectionManager;
class DataBaseConnection;
class ServerController {



public:

    ServerController();
    static void selectAction(int fd, json messageJson, ConnectionManager &cm, DataBaseConnection &dbc);
    static void sendResponse(int fd, string response, ConnectionManager &cm);

    static string userLogin(string, string, DataBaseConnection &dbc);
    static string userRegistration(string, string, DataBaseConnection &dbc);
    static string userGroups(int userId, DataBaseConnection &dbc);
    static string allGroups(DataBaseConnection &dbc);
    static string makeGroup(int userId, string groupName, DataBaseConnection &dbc);

};


#endif //SERVER_PROTOTYPE_SERVERCONTROLLER_H
