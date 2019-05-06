//
// Created by marjan on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_GROUP_H
#define SERVER_PROTOTYPE_GROUP_H


#include <string>

class Group {
    long id;
    std::string name;
    long leaderId;

    Group(long, std::string, long);
};


#endif //SERVER_PROTOTYPE_GROUP_H
