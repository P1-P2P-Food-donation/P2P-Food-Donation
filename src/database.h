//
// Created by feddersen on 16/11/2023.
//

#ifndef P2P_FOOD_DONATION_DATABASE_H
#define P2P_FOOD_DONATION_DATABASE_H

#endif //P2P_FOOD_DONATION_DATABASE_H

#include "timestamp.h"

enum user_role{role_admin, role_user};
enum item_category{fruit, vegetable, meat};

struct bid{
    int item_id;
    struct user* user;
    int amount;
};

struct user{
    char username[30];
    char password[30];
    char phone_number[15];
    int points;
    enum user_role role;
};

struct item{
    int id;
    struct user* owner;
    struct timestamp timestamp;
    char title[30];
    char description[100];
    char location[100];
    enum item_category category;
    int quantity;
};

struct Bid_Node {
    struct bid* data;
    struct Bid_Node* next;
};

struct User_Node {
    struct user data;
    struct User_Node* next;
};

//Items

void print_items();
void add_item(char seller_name[], char title[], char description[], char location[], enum item_category category, int quantity, struct timestamp end_time);
void update_item_file();
struct Item_Node* get_items_from_user(char username[]);
int delete_item(int item_id);

//Users
void print_users();
void add_user(char* username, char* password, char* phone_number, int points, enum user_role role);
struct user* get_user(char* username);
void update_user_file();
int delete_user(char username[]);

//Bids
struct Bid_Node* get_bids_with_id(int item_id);
void add_bid(int item_id, struct user* bidder, int bid_amount);
void update_bid_file();
void print_bids();

//General
void load_data_from_csv();