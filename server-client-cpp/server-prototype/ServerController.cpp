//
// Created by michal on 06.05.19.
//

#include "ServerController.h"
#include "nlohmann/json.hpp"
#include "ClientStructure.h"
#include "DataBaseConnection.h"
#include "ConnectionManager.h"
#include "PackageSizeParser.h"
#include "ResponseFlag.h"
#include <string>
#include <iostream>
#include <cstring>
#include <boost/config.hpp>


using namespace nlohmann;
using namespace std;


ResponseFlag convert(const std::string& str)
{
    if(str == "LOGGING") return LOGGING;
    else if(str == "REGISTR") return REGISTR;

}


ServerController::ServerController() {

}

void ServerController::selectAction(int fd, json messageJson, ConnectionManager &cm, DataBaseConnection &dbc) {
    string response;
    ResponseFlag enumFlag = convert(messageJson["flag"]);

    switch(enumFlag) {
        case LOGGING:
            response = userLogin(messageJson["username"], messageJson["password"] , dbc);
            break;
        case REGISTR:
            response = userRegistration(messageJson["username"], messageJson["password"], dbc);
            break;
        default:
            cout << "default switch" << endl;
            break;
    }

    sendResponse(fd, response, cm);
}

void ServerController::sendResponse(int fd, string response, ConnectionManager &cm){
    char header[4];
    PackageSizeParser::serialize_int_32(header, response.size());

    char messageResponse[response.size()];
    memcpy(messageResponse, response.c_str(), response.size());

    char whole_pack[response.size()+4];
    memcpy(whole_pack, header, 4);
    memcpy(&whole_pack[4], messageResponse, response.size());

    int bytes = response.size()+4;

    if (cm.send_all(fd, whole_pack, &bytes) == -1) {
        perror("send");
        printf("~~ Sent only %d bytes (error) \n", bytes);
    }

}

string ServerController::userLogin(string userName, string userPassword, DataBaseConnection &dbc) {
    string returnMessage;

    if (!dbc.correctLogon(userName, userPassword)) {
        returnMessage = "{\"flag\":\"__ERROR\"}";
    } else {
        returnMessage = "{\"flag\":\"LOGGING\"";
        returnMessage += dbc.userLoginData(userName);
    }
    return returnMessage;
}

string ServerController::userRegistration(string userName, string userPassword, DataBaseConnection &dbc) {
    string returnMessage;

    if (!dbc.correctRegistration(userName, userPassword)) {
        returnMessage = "{\"flag\":\"__ERROR\"}";
    } else {
        returnMessage = "{\"flag\":\"REGISTR\"}";
    }
    return returnMessage;
}
