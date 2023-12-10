//
// Created by feddersen on 16/11/2023.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

// User and item linked lists
struct User_Node {
    struct user data;
    struct User_Node* next;
};
struct Item_Node {
    struct item data;
    struct Item_Node* next;
};

struct User_Node* users = NULL;
struct Item_Node* items = NULL;
struct Bid_Node* bids = NULL;

// Users [PRIVATE]

void import_user_file(){

    FILE* file = fopen("users.csv", "r");

    if(file == NULL){
        printf("Couldn't open users.csv");
        exit(EXIT_FAILURE);
    }

    while(!feof(file)){
        struct user u;
        int success_amount = fscanf(file, "%[^,], %[^,], %[^,], %d, %d\n", u.username, u.password, u.phone_number, &u.points, &u.role);
        if(success_amount != 5){
            printf("Error importing users.csv, %d", success_amount);
            exit(EXIT_FAILURE);
        }

        //Allocate memory and handle out of memory case
        struct User_Node* new_node = (struct User_Node*) malloc(sizeof(struct User_Node));
        if(new_node == NULL){
            printf("Out of memory");
            exit(EXIT_FAILURE);
        }

        new_node->data = u;
        new_node->next = users;

        users = new_node;
    }
}

void save_user_to_file(struct user u){
    FILE* file = fopen("users.csv", "a"); //Open file in append mode

    fprintf(file, "%s, %s, %s, %d, %d\n", u.username, u.password, u.phone_number, u.points, u.role); //Write user to file

    fclose(file); //Close file
}

// Users [PUBLIC]

void print_users(){

    struct User_Node* rest_users = users;

    printf("USERS\n");
    while(rest_users != NULL){
        printf("User: %s, Points: %d\n", rest_users->data.username, rest_users->data.points);
        rest_users = rest_users->next;
    }
    printf("\n\n");
}

void add_user(char* username, char* password, char* phone_number, int points, enum user_role role){

    //Checks if username, password and phone_number are strings of acceptable sizes.
    if(strlen(username) > 30){
        printf("username cant be bigger than 29 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(password) > 30){
        printf("password cant be bigger than 29 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(phone_number) > 15){
        printf("phone number cant be bigger than 14 characters");
        exit(EXIT_FAILURE);
    }

    //Create the new entry
    struct user new_entry;
    strncpy(new_entry.username, username, 30);
    strncpy(new_entry.password, password, 30);
    strncpy(new_entry.phone_number, phone_number, 15);
    new_entry.points = points;
    new_entry.role = role;

    //Allocate memory and handle out of memory case
    struct User_Node* new_node = (struct User_Node*) malloc(sizeof(struct User_Node));
    if(new_node == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    //Save user
    save_user_to_file(new_entry);

    //Create a new node and make it the new head of the linked list
    new_node->data = new_entry;
    new_node->next = users;
    users = new_node;
}

void update_user_file(){
    //Clear file
    FILE* file = fopen("users.csv", "w");
    fclose(file);

    //Loop through linked list and add every node to file
    struct User_Node* rest_users = users;
    while(rest_users != NULL){
        save_user_to_file(rest_users->data);
        rest_users = rest_users->next;
    }
}

struct user* get_user(char* username){

    struct User_Node* rest_users = users;

    while(rest_users != NULL){
        //Test if current index of linked list is the user with username
        if(strcmp(rest_users->data.username, username) == 0){
            return &rest_users->data;
        }
        rest_users = rest_users->next;
    }
    return NULL; // No user with that username was found
}

// Items [PRIVATE]

void import_item_file(){

    FILE* file = fopen("items.csv", "r");

    if(file == NULL){
        printf("Couldn't open items.csv");
        exit(EXIT_FAILURE);
    }

    while(!feof(file)){
        struct item i;
        struct timestamp t;

        char username[30];

        int success_amount = fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %d, %d, %d:%d:%d, %d/%d/%d\n", &i.id, username, i.title, i.description, i.location, &i.category, &i.quantity, &t.hour, &t.minute, &t.seconds, &t.day, &t.month, &t.year);
        if(success_amount != 13){
            printf("Error importing items.csv, %d", success_amount);
            exit(EXIT_FAILURE);
        }
        i.timestamp = t;

        //Find user
        struct user* u = get_user(username);
        if(u == NULL){
            printf("Error importing items.csv: The user %s was not found", username);
            exit(EXIT_FAILURE);
        }
        i.owner = u;


        //Allocate memory and handle out of memory case
        struct Item_Node* new_node = (struct Item_Node*) malloc(sizeof(struct Item_Node));
        if(new_node == NULL){
            printf("Out of memory");
            exit(EXIT_FAILURE);
        }

        new_node->data = i;
        new_node->next = items;

        items = new_node;
    }
}

void save_item_to_file(struct item i){
    FILE* file = fopen("items.csv", "a"); //Open file in append mode

    fprintf(file, "%d, %s, %s, %s, %s, %d, %d, %d:%d:%d, %d/%d/%d\n", i.id, i.owner->username, i.title, i.description, i.location, i.category, i.quantity, i.timestamp.hour, i.timestamp.minute, i.timestamp.seconds, i.timestamp.day, i.timestamp.month, i.timestamp.year);

    fclose(file); //Close file
}

// Items [PUBLIC]

void print_items(){

    struct Item_Node* rest_items = items;

    while(rest_items != NULL){
        printf("id: %d\n", rest_items->data.id);
        rest_items = rest_items->next;
    }
}

void add_item(char seller_name[], char title[], char description[], char location[], enum item_category category, int quantity, struct timestamp end_time){

    if(strlen(title) > 30){
        printf("title can't be longer than 30 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(description) > 100){
        printf("description can't be longer than 100 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(location) > 100){
        printf("location can't be longer than 100 characters");
        exit(EXIT_FAILURE);
    }

    //Find the highest id and store it as highest_id
    int highest_id = 0;
    struct Item_Node* rest_items = items;

    while(rest_items != NULL){
        if(rest_items->data.id > highest_id){
            highest_id = rest_items->data.id;
        }
        rest_items = rest_items->next;
    }


    //Initialize the new item.
    struct item new_item;
    new_item.id = highest_id + 1;
    new_item.owner = get_user(seller_name);
    new_item.timestamp = end_time;
    strncpy(new_item.title, title, 30);
    strncpy(new_item.description, description, 100);
    strncpy(new_item.location, location, 100);
    new_item.category = category;
    new_item.quantity = quantity;

    //Save to file
    save_item_to_file(new_item);

    //Allocate memory and handle out of memory case
    struct Item_Node* new_node = (struct Item_Node*) malloc(sizeof(struct Item_Node));
    if(new_node == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    new_node->data = new_item;
    new_node->next = items;
    items = new_node;
}

void update_item_file(){
    //Clear file
    FILE* file = fopen("items.csv", "w");
    fclose(file);

    //Loop through linked list and add every node to file
    struct Item_Node* rest_items = items;
    while(rest_items != NULL){
        save_item_to_file(rest_items->data);
        rest_items = rest_items->next;
    }
}

// Bids [PRIVATE]
void import_bid_file(){

    FILE* file = fopen("bids.csv", "r");

    if(file == NULL){
        printf("Couldn't open bids.csv");
        exit(EXIT_FAILURE);
    }

    while(!feof(file)){
        //Scan line from file
        struct bid* b = (struct bid*)malloc(sizeof(struct bid));
        char username[30];
        int success_amount = fscanf(file, "%d, %[^,], %d\n", &b->item_id, username, &b->amount);
        if(success_amount != 3){
            printf("Error importing bids.csv");
            exit(EXIT_FAILURE);
        }

        //Gets user from username
        struct user* u = get_user(username);
        if(u == NULL){
            printf("Error importing bid because username %s doesn't exist", username);
            exit(EXIT_FAILURE);
        }
        b->user = u;

        //Allocate memory and handle out of memory case
        struct Bid_Node* new_node = (struct Bid_Node*) malloc(sizeof(struct Bid_Node));
        if(new_node == NULL){
            printf("Out of memory");
            exit(EXIT_FAILURE);
        }

        //printf("%s, %d", b->user->username, b->item_id);

        //Add the new node to the head of the linked list
        new_node->data = b;
        new_node->next = bids;
        bids = new_node;
    }
}

void save_bid_to_file(struct bid b){
    FILE* file = fopen("bids.csv", "a"); //Open file in append mode

    fprintf(file, "%d, %s, %d\n", b.item_id, b.user->username, b.amount);

    fclose(file); //Close file
}

// Bids [PUBLIC]
/**
 * Returns true if bid was successful and false if the bid was not successful
 */
void add_bid(int item_id, struct user* bidder, int bid_amount){

    //struct bid b = {item_id, bidder, bid_amount};
    struct bid* b = (struct bid*) malloc(sizeof(struct bid));
    if(b == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }
    b->item_id = item_id;
    b->user = bidder;
    b->amount = bid_amount;

    //Add to bids.csv
    save_bid_to_file(*b);

    //Add bid to linked list
    struct Bid_Node* new_node = (struct Bid_Node*) malloc(sizeof(struct Bid_Node));
    if(new_node == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }

    //Add bid to the head of the linked list
    new_node->data = b;
    new_node->next = bids;
    bids = new_node;
}

struct Bid_Node* get_bids_with_id(int item_id){
    struct Bid_Node* linked_list = NULL;
    struct Bid_Node* index = bids;
    while(index != NULL){
        if(index->data->item_id == item_id){
            struct Bid_Node* new_node = (struct Bid_Node*) malloc(sizeof(struct Bid_Node));
            new_node->data = index->data;
            new_node->next = linked_list;
            linked_list = new_node;
            //printf("%s, %d", linked_list->data->user->username, linked_list->data->item_id);
        }
        index = index->next;
    }
    return linked_list;
}

void update_bid_file(){
    //Clear file
    FILE* file = fopen("bids.csv", "w");
    fclose(file);

    //Loop through linked list and add every node to file
    struct Bid_Node* rest_items = bids;
    while(rest_items != NULL){
        save_bid_to_file(*rest_items->data);
        rest_items = rest_items->next;
    }
}

void print_bids(){
    struct Bid_Node* rest_bids = bids;

    printf("BIDS\n");
    while(rest_bids != NULL){
        printf("%d %s %d\n", rest_bids->data->item_id, rest_bids->data->user->username, rest_bids->data->amount);
        rest_bids = rest_bids->next;
    }
    printf("\n\n");
}

// General
void load_data_from_csv(){
    import_user_file();
    import_item_file();
    import_bid_file();
}