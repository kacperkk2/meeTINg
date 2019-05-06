//
// Created by marjan on 06.05.19.
//

#ifndef SERVER_PROTOTYPE_OFFER_H
#define SERVER_PROTOTYPE_OFFER_H


class Offer {
    long id;
    long eventId;
    //TODO startDate date?
    int startDate;
    int votesCount;
    bool acceptedOffer;

    Offer(long, long, int, int, bool);
};


#endif //SERVER_PROTOTYPE_OFFER_H
