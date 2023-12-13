//
// Created by Emil on 27-11-2023.
//

#ifndef P2P_FOOD_DONATION_INTERFACE_H
#define P2P_FOOD_DONATION_INTERFACE_H

struct menu_item {
    char* string;
    int (*function)();
};
int printMessage();

int printscan_menu(struct menu_item menu[], int size);

int delete_user_scan();
int delete_item_scan();
int make_bid_scan();
int auctionise_item_scan();
int print_all_users();
int print_all_unexpired_items();

#endif //P2P_FOOD_DONATION_INTERFACE_H
