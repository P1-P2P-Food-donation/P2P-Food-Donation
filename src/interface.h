//
// Created by Emil on 27-11-2023.
//

#ifndef P2P_FOOD_DONATION_INTERFACE_H
#define P2P_FOOD_DONATION_INTERFACE_H

struct menu_item {
    char* string;
    void (*function)();
};

int printMessage();
void printscan_menu(struct menu_item menu[], int size);
void delete_user_scan();
void delete_item_scan();
void make_bid_scan();
void auctionise_item_scan();
void print_all_users();
void print_all_unexpired_items();
void my_auction_and_bids();
void display_points();

#endif //P2P_FOOD_DONATION_INTERFACE_H
