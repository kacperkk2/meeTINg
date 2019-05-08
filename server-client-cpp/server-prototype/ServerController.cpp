//
// Created by michal on 06.05.19.
//

#include "ServerController.h"
#include "nlohmann/json.hpp"
#include "ClientStructure.h"
#include "DataBaseConnection.h"
#include "ConnectionManager.h"
#include <string>
#include <iostream>
#include <cstring>
//#include "ResponseFlag.h"

using namespace nlohmann;
using namespace std;




ServerController::ServerController() {

    string message = "0000LOGGING{\"username\": \"tomasz\",\"password\": \"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3\"}";


}

void ServerController::selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc) {
    int f =1;
    //string message = client.get_buffer_message();
    string message = "0000LOGGING{\"username\": \"tomasz\",\"password\": \"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3\"}";
    string flag = message.substr(4, 7);
    string data = message.substr(11);
    string response;

    switch (f) {
        case 1:
            response = logonData(data, cm, dbc);git a
            break;
        default:
            cout << "nie ma logowania" << endl;
            break;
    }
    response = "0007" + response;
    sendResponse(fd, response, response.length(),cm);

}


string ServerController::ServerController::logonData(string message, ConnectionManager &cm, DataBaseConnection &dbc) {
    string returnMessage;
    auto j = json::parse(message);
    if (dbc.correctLogon(j["username"], j["password"])) {
        returnMessage = "LOGGING";
    } else {
        returnMessage = "__ERROR";
    }
    return returnMessage;
}

void ServerController::sendResponse(int fd, string response, int responseSize, ConnectionManager &cm) {
    cout << response<< responseSize<<endl;
    const char *c = response.c_str();
    char *p = new char[response.length()];
    memcpy(p, c, response.length());
    cm.send_all(fd, p, &responseSize);
}

