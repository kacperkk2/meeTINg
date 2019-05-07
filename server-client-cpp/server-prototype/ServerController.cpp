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
    //cm = ConnectionManager();
    //dbc = DataBaseConnection("admin", "admin");
    //cm = ConnectionManager();
    string blad = "ERROR";
    //cout << blad.c_str()<<endl;
    const char *c = blad.c_str();
    //cout<< typeid(blad.c_str()).name() << endl;
    string message = "{\"id\": 1,\"username\": \"tomasz\",\"password\": \"123\",\"systemRole\": \"USER\"}";
    auto j = json::parse(message);
    cout << j["id"]<<endl;

}

void ServerController::selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc) {
    int f =1;
    cout<<"selectakszyn"<<endl;
    string message = client.get_buffer_message();
    string flag = message.substr(4, 11);
    string data = message.substr(11);
    cout << data<<endl;
    cout<< flag <<endl;
    string response;

    switch (f) {
        case 1:
            response = logonData(data,cm, dbc);
            break;
        default:
            cout << "nie ma logowania" << endl;
            break;
    }

    sendResponse(fd, response, response.length(),cm);

}


string ServerController::ServerController::logonData(string message2, ConnectionManager &cm, DataBaseConnection &dbc) {

    string message = "{\"id\": 1,\"username\": \"tomasz\",\"password\": \"123\",\"systemRole\": \"USER\"}";
    string returnMessage = "LOGGING";

    auto j = json::parse(message);
    if (dbc.correctLogon(j["username"], j["password"])) {
        returnMessage = "LOGGING";
    } else {
        returnMessage = "__ERROR";
    }
    cout << returnMessage;
    return returnMessage;
}

void ServerController::sendResponse(int fd, string response, int responseSize, ConnectionManager &cm) {
    cout << "doszedlem" << endl;
    int *s = (int *) responseSize;
    const char *c = response.c_str();
    char *p = new char[response.length()];
    memcpy(p, c, response.length());

    cm.send_all(fd, p, s);
}

