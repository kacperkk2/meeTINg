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

    string message = "0000LOGGING{\"username\": \"tomasz\",\"password\": \"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3\"}";


}

void ServerController::selectAction(int fd, ClientStructure client, ConnectionManager &cm, DataBaseConnection &dbc) {
    int f =1;
    //string message = client.get_buffer_message();
    string message = "0000LOGGING{\"username\": \"tomasz\",\"password\": \"a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3\"}";
    string flag = message.substr(4, 7);
    string data = message.substr(11);
    string response;
    char buf[4];

    switch (f) {
        case 1:
            response = logonData(data, cm, dbc);
            break;
        default:
            cout << "nie ma logowania" << endl;
            break;
    }
    int32_t m_size = response .size();
    PackageSizeParser::serialize_int_32(buf, m_size);


    string  mr;
    mr = buf[0];
    mr.push_back(buf[1]);
    mr.push_back(buf[2]);
    mr.push_back(buf[3]);
    mr.append(response);


    sendResponse(fd, mr, mr.length(),cm);

}


string ServerController::logonData(string message, ConnectionManager &cm, DataBaseConnection &dbc) {
    string returnMessage = "LOGGING";
//    auto j = json::parse(message);
//    if (dbc.correctLogon(j["username"], j["password"])) {
//        returnMessage = "LOGGING";
//    } else {
//        returnMessage = "__ERROR";
//    }
    return returnMessage;
}

void ServerController::sendResponse(int fd, string response, int responseSize, ConnectionManager &cm) {
    const char *c = response.c_str();
    char p[response.length() + 1];
    //strcpy(p, response.c_str());
    memcpy(p, c, response.length());
    for (int i = 0; i < response.length(); i++) {
        cout << p[i];
    }
    cout << endl;
    cm.send_all(fd, p, &responseSize);
}

//void ServerController::sendResponse(int fd, string response, int responseSize, ConnectionManager &cm) {
//    //const char *c = response.c_str();
//    char p[response.length() + 1];
//    strcpy(p, response.c_str());
//    //memcpy(p, c, response.length());
//    cout << p << endl;
//    for (int i = 0; i < response.length(); i++)
//        cout << p[i];
//    cm.send_all(fd, p, &responseSize);
//}


//cout << strlen(p) << endl;
//cout << p[0] << p[1] << p[2] << p[3]<< p[4] << p[5] << p[6] << p[7]<< p[8]<< p[9] << p[10] << p[11] <<p[12] << p[13] << p[14] << p[15] <<p[16] << p[17]<<endl;

