//
// Created by michal on 06.05.19.
//

#include "ServerController.h"
#include "nlohmann/json.hpp"
#include "ClientStructure.h"
#include "DataBaseConnection.h"
#include "ConnectionManager.h"
#include "PackageSizeParser.h"
#include <string>
#include <iostream>
#include <cstring>
//#include "ResponseFlag.h"

using namespace nlohmann;
using namespace std;




ServerController::ServerController() {

    //string message = "0000LOGGING{\"username\": \"tomasz\",\"password\": \"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3\"}";


}

void ServerController::selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc) {
    int f =1;
    int messageSize = client.get_whole_package_size();
    char messageChar[messageSize];
    memcpy(messageChar, client.get_buffer_message(), messageSize);
    string message(messageChar, messageSize);
    string flag = message.substr(4, 7);
    string data = message.substr(11);
    string response;


    switch (f) {
        case 1:
            response = userLogin(data, cm, dbc);
            break;
        default:
            cout << "nie ma logowania" << endl;
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
    string returnMessage = "LOGGING";
    string userData = "{\n\"id\": \"1\",\n \"username\": \"asd123_#\",\n \"password\": \"b790d976a02850ac9d5605e92ac7283ac477c76c203556fdd94726dd106cdae3\",\n \"systemRole\": \"TEAM_LEADER\"\n}";

    auto j = json::parse(message);
    if (!dbc.correctLogon(j["username"], j["password"])) {
        returnMessage = "__ERROR";
    } else {
        returnMessage = "LOGGING";
    }
    return returnMessage+userData;
}
