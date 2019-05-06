//
// Created by marjan on 06.05.19.
//

#include "Offer.h"

Offer::Offer(long id, long eId,int startDate, int votesCount,bool acceptedOffer) {
    this->id = id;
    this->eventId = eId;
    this->startDate = startDate;
    this->votesCount = votesCount;
    this->acceptedOffer = acceptedOffer;
}