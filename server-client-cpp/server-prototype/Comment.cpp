//
// Created by marjan on 06.05.19.
//

#include "Comment.h"

Comment::Comment(long id, long userId, long eventId, std::string message, int date) {
    this->id = id;
    this->userId = userId;
    this->eventId = eventId;
    this->message = message;
    this->date = date;
}