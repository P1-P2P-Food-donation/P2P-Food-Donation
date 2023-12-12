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

#endif //P2P_FOOD_DONATION_INTERFACE_H
