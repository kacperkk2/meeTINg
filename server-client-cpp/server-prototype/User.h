//
// Created by marjan on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_USER_H
#define SERVER_PROTOTYPE_USER_H


#include <string>

class User {
    long id;
    std::string username;
    std::string hashedPassword;
    bool isLeader;

    User(long, std::string, std::string, bool);
};


#endif //SERVER_PROTOTYPE_USER_H
