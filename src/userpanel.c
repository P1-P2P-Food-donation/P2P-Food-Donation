//
// Created by Jeppe Nyland Mortensen on 29/11/2023.
//


#include "interface.h"
#include "login.h"
#include "auction.h"




/**
 * This function is used to display the auction menu.
 * It displays the options available to the user, such as listing items, making a bid, auctioning an item, displaying points, and viewing their auctions/bids.
 */
void auction_menu() {
    struct menu_item menu[5] = {
            {"List items", &print_all_unexpired_items},
            {"Make a bid", &make_bid_scan},
            {"Auction item", &auctionise_item_scan},
            {"Display points", &display_points},
            {"My auctions/bids", &my_auction_and_bids},
    };
    printscan_menu(menu, 5);
}

/**
 * This function is used to display the user menu.
 * It displays the options available to the user.
 */
void user_menu() {
    struct menu_item menu[1] = {
            {"Auction menu", &auction_menu}
    };

    printscan_menu(menu, 1);
}

/**
 * This function is used to display the admin menu.
 * It creates an array of menu_item structures, each of which consists of a string and a function pointer.
 * The function then calls printscan_menu with this array and its size.
 * The printscan_menu function prints each menu item and scans the user's choice, then calls the function corresponding to the user's choice.
 */
void admin_menu() {
    struct menu_item menu[4] = {
            {"Auction menu", &auction_menu},
            {"List users", &print_all_users},
            {"Delete a user", &delete_user_scan},
            {"Delete a item", &delete_item_scan}
    };
    printscan_menu(menu, 4);
}

//Helper functions
/**
 * Runs admin menu, if user is admin otherwise runs user menu
 */
void admin_check(){
    if(current_user->role == role_admin){
        admin_menu();
    } else {
        user_menu();
    }
}

/**
 * Runs admin_check if login was successful
 */
void login_handler(){
    if(login()){
        admin_check();
    } else {
        return;
    }
}

/**
 * Runs admin_check if register was successful
 */
void register_handler(){
    if(create_user()){
        admin_check();
    } else {
        return;
    }
}

/**
 * This function is used to display the menu for users who are not logged in.
 * It displays the options to login or create a new user.
 */
void not_logged_in_menu() {
    struct menu_item menu[2] = {
            {"Login", &login_handler},
            {"Create user", &register_handler}
    };
    printscan_menu(menu, 2);
}

/**
 * This function is used to start the application.
 * It loads the data from the CSV files, displays the not logged in login menu.
 */
void start_application(){
    load_data_from_csv();

    not_logged_in_menu();
}