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


using namespace nlohmann;
using namespace std;


ResponseFlag convert(const std::string& str)
{
    if(str == "LOGGING") return LOGGING;
    else if(str == "REGISTR") return REGISTR;

}



ServerController::ServerController() {

}

void ServerController::selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc) {
    ResponseFlag enumFlag;
    int messageSize = client.get_whole_package_size();
    char messageChar[messageSize];
    memcpy(messageChar, client.get_buffer_message(), messageSize);
    string message(messageChar, messageSize);
    string flag = message.substr(4, 7);
    string data = message.substr(11);
    string response;
    enumFlag = convert(flag);


    //enumFlag = REGISTR;
    switch(enumFlag) {
        case LOGGING:
            response = userLogin(data, cm, dbc);
            break;
        case REGISTR:
            response = userRegistration(data, cm, dbc);
            break;
        default:
            cout << "default switch" << endl;
            break;
    }

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

string ServerController::userLogin(string message, ConnectionManager &cm, DataBaseConnection &dbc) {
    string returnMessage;
    auto j = json::parse(message);

    if (!dbc.correctLogon(j["username"], j["password"])) {
        returnMessage = "__ERROR";
    } else {
        returnMessage = "LOGGING";
        returnMessage += dbc.userLoginData(j["username"]);
    }
    return returnMessage;
}

string ServerController::userRegistration(string message, ConnectionManager &cm, DataBaseConnection &dbc) {
    string returnMessage;
    auto j = json::parse(message);

    if (!dbc.correctRegistration(j["username"], j["password"])) {
        returnMessage = "__ERROR";
    } else {
        returnMessage = "REGISTR";
        //returnMessage += dbc.userLoginData(j["username"]);
    }
    return returnMessage;
}
