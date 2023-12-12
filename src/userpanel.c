//
// Created by Jeppe Nyland Mortensen on 29/11/2023.
//

#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "interface.h"
//#include "buy_and_sell.h"
#include "login.h"
#include "auction.h"
#include "interface.h"


int auktion_menu() {
    const int menu_size = 1;
    struct menu_item menu[2] = {
            {"Auctionise item", &auctionise_item_scan},
            {"Make a bid", &make_bid_scan}
    };
    printscan_menu(menu, 2);
    return 0;
}

void user_menu() {
    struct menu_item menu[1] = {
//            {"Sell food", &sell_food},
//            {"Buy food", &buy_food},
            {"Auction menu", &auktion_menu}
    };

    printscan_menu(menu, 1);
}

int admin_menu() {
    struct menu_item menu[3] = {
//            {"Sell food", &sell_food},
//            {"Buy food", &buy_food},
            {"Auction menu", &auktion_menu},
            {"Delete a user", &delete_user_scan},
            {"Delete a item", &delete_item_scan}
    };
    printscan_menu(menu, 3);
    return 0;
}


void not_logged_in_menu() {
    const int menu_size = 1;
    struct menu_item menu[2] = {
            {"Login", &login},
            {"Create user", &create_user}
    };
    printscan_menu(menu, 2);
}


void start_application(){
    load_data_from_csv();

    not_logged_in_menu();

    //current_user is NULL if and only if last menu was exited
    if(current_user != NULL){
            if (current_user->role == role_admin) {
                admin_menu();
            }
            else {
                user_menu();
            }
    }
}