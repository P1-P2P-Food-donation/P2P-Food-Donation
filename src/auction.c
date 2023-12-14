//
// Created by feddersen on 10.12.23.
//

#include "auction.h"
#include "stdio.h"
#include "strings.h"

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
/**
 * This function is used to place a bid on an item in the auction.
 * It first checks if the bid is higher than the current highest bid.
 * If the user has already placed a bid, it lowers the required amount.
 * If the new bid is lower than the existing bid, it returns an error.
 * It then checks if the user has enough points to place the bid.
 * If the user has enough points, it updates the user's points and the bid file.
 * If the user doesn't have enough points, it returns an error.
 *
 * @param item_id The ID of the item on which the bid is being placed.
 * @param bidder The user who is placing the bid.
 * @param bid_amount The amount of the bid being placed.
 * @return Returns 1 if the bid was placed successfully, 0 otherwise.
 */
int make_bid(int item_id, struct user* bidder, int bid_amount){

    //Check to see if bid is higher than the highest bid
    struct bid* highest_bid = get_highest_bid(item_id);
    if(highest_bid != NULL){
        if(bid_amount <= highest_bid->amount && strcmp(highest_bid->user->username, bidder->username) != 0){
            printf("A higher or equal bid of %d has already been placed by %s", highest_bid->amount, highest_bid->user->username);
            return 0;
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
                printf("Bid is invalid because you already have placed a higher bid (new bid: %d < old bid %d)\n", bid_amount, linked_list->data->amount);
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
    } else {
        printf("Bid was placed successfully\n");
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
