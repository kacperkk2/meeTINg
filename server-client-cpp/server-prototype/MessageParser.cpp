//
// Created by michal on 18.05.19.
//

#include "MessageParser.h"

using namespace std;

MessageParser::MessageParser(){

}

json MessageParser::parseRequest(ClientStructure client){
    int messageSize = client.get_whole_package_size();
    char messageChar[messageSize];

    memcpy(messageChar, client.get_buffer_message(), messageSize);
    string message(messageChar, messageSize);
    string data = message.substr(4);
    auto j = json::parse(data);

    return j;
}
