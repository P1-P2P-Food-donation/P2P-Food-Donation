//
// Created by feddersen on 10.12.23.
//

#include "auction.h"
#include "stdio.h"

// Returns the winning bid
struct bid* get_highest_bid(int item_id){
    struct Bid_Node* index = get_bids_with_id(item_id);
    struct bid* champion = NULL;
    //Make sure that champion contains the highest bid
    while(index != NULL){
        if(champion == NULL || index->data->amount > champion->amount){
            champion = index->data;
        }
        index = index->next;
    }
    return champion;
}

// Returns 1 if bid was placed successfully or 0 if an error occurred
int make_bid(int item_id, struct user* bidder, int bid_amount){

    //Check to see if bid is higher than the highest bid
    struct bid* highest_bid = get_highest_bid(item_id);
    if(highest_bid != NULL){
        if(bid_amount <= highest_bid->amount){
            printf("A higher bid has already been place: %d, your bid was only: %d", highest_bid->amount, bid_amount);
        }
    }

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
