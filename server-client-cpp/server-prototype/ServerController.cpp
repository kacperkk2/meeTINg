//
// Created by michal on 06.05.19.
//

#include "ServerController.h"
#include "nlohmann/json.hpp"
#include "ClientStructure.h"
#include "DataBaseConnection.h"

using namespace std;
using namespace nlohmann;


ServerController::ServerController() {

}

void ServerController::selectAction(int fd, ClientStructure client){
    int f;

    string message = client.get_buffer_message();
    string flag = message.substr(0,7);
    string data = message.substr(7);

    if(flag == "LOGGING") f = 1;
    switch(f)
    {
        case 1:
            logonData(data);
            break;
        default:
            cout<<"nie ma logowania"<<endl;
            break;
    }

}


string ServerController::ServerController::logonData(string message2) {

    string message = "{\"id\": 1,\"username\": \"tomasz\",\"password\": \"123\",\"systemRole\": \"USER\"}";
    string returnMessage;
    auto j = json::parse(message);
    if (dbc.correctLogon(j["username"], j["password"])) {
        returnMessage = "LOGGIN";
    } else {
        returnMessage = "ERROR";
    }
    cout << returnMessage;
    return returnMessage;
}

