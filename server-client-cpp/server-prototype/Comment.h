//
// Created by marjan on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_COMMENT_H
#define SERVER_PROTOTYPE_COMMENT_H

#include <string>

class Comment {
    long id;
    long userId;
    long eventId;
    std::string message;
    //TODO date?
    int date;

    Comment(long, long, long, std::string, int);
};


#endif //SERVER_PROTOTYPE_COMMENT_H
