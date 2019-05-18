//
// Created by michal on 18.05.19.
//

#ifndef SERVER_PROTOTYPE_MESSAGEPARSER_H
#define SERVER_PROTOTYPE_MESSAGEPARSER_H

#include "nlohmann/json.hpp"
#include "ClientStructure.h"

using namespace nlohmann;

class MessageParser {

public:
    MessageParser();
    static json parseRequest(ClientStructure client);

};


#endif //SERVER_PROTOTYPE_MESSAGEPARSER_H
