//
// Created by feddersen on 10.12.23.
//

#ifndef P2P_FOOD_DONATION_AUCTION_H
#define P2P_FOOD_DONATION_AUCTION_H
// #includes
#include "database.h"

// function prototypes
int make_bid(int item_id, struct user* bidder, int bid_amount);
struct bid* get_highest_bid(int item_id);

#endif //P2P_FOOD_DONATION_AUCTION_H
