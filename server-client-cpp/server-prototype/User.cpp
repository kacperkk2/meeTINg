//
// Created by marjan on 06.05.19.
//

#include "User.h"

User::User(long id, std::string username, std::string hashedPassword, bool isLeader) {
    this->id = id;
    this->username = username;
    this->hashedPassword = hashedPassword;
    this->isLeader = isLeader;
}