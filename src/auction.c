//
// Created by feddersen on 10.12.23.
//

#include "auction.h"
#include "stdio.h"


int make_bid(int item_id, struct user* bidder, int bid_amount){

    int required_amount = bid_amount;

    struct Bid_Node* linked_list = get_bids_with_id(item_id);
    struct bid* existing_bid = NULL;

    //Lower required amount if bid has already been placed
    while(linked_list != NULL){
        if(linked_list->data->user->username == bidder->username){
            required_amount -= linked_list->data->amount;
            existing_bid = linked_list->data;

            //Fail if new bid is lower than existing bid
            if(required_amount < 0){
                printf("Bid is invalid because you already have a higher bid (new bid: %d < old bid %d)\n", bid_amount, linked_list->data->amount);
                return 0;
            }

            break;
        }
        linked_list = linked_list->next;
    }

    //Check if the bidder has the points needed
    if(required_amount > bidder->points){
        printf("Insufficient funds. You need: %d to make this bid\n", required_amount - bidder->points);
        return 0;
    }

    //Update previous bid or make new
    if(existing_bid == NULL){
        bidder->points -= required_amount;
        update_user_file();
        add_bid(item_id, bidder, bid_amount);
    } else {
        bidder->points -= required_amount;
        existing_bid->amount = bid_amount;
        update_bid_file();
        update_user_file();
    }
    return 1;
}
