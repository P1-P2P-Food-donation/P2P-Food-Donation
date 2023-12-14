//
// Created by feddersen on 16/11/2023.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "auction.h"

// User and item linked lists
struct Item_Node {
    struct item data;
    struct Item_Node* next;
};

struct User_Node* users = NULL;
struct Item_Node* items = NULL;
struct Bid_Node* bids = NULL;

//Function headers
void delete_bid_id(int item_id);
void delete_bid_username(char username[]);

/* - - - - - - - USERS - - - - - - - - -*/

// Users [PRIVATE]
/**
 * This function is used to import user data from a file.
 * It reads the file line by line and creates a new user node for each line.
 * Each user node is added to the global linked list of users.
 */
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

/**
 * This function is used to save a user to a file.
 * It opens the file in append mode and writes the user data to the file.
 *
 * @param u The user to be saved to the file.
 */
void save_user_to_file(struct user u){
    FILE* file = fopen("users.csv", "a"); //Open file in append mode

    fprintf(file, "%s, %s, %s, %d, %d\n", u.username, u.password, u.phone_number, u.points, u.role); //Write user to file

    fclose(file); //Close file
}

// Users [PUBLIC]
/**
 * This function is used to print all users.
 * It iterates over the global linked list of users and prints each user's username and points.
 */
void print_users(){

    struct User_Node* rest_users = users;

    printf("USERS\n");
    while(rest_users != NULL){
        printf("Username: %s, Points: %d\n", rest_users->data.username, rest_users->data.points);
        rest_users = rest_users->next;
    }
    printf("\n");
}

/**
 * This function is used to add a new user.
 * It creates a new user node and adds it to the global linked list of users.
 * It also saves the new user to a file.
 *
 * @param username The username of the new user.
 * @param password The password of the new user.
 * @param phone_number The phone number of the new user.
 * @param points The initial points of the new user.
 * @param role The role of the new user.
 */
void add_user(char* username, char* password, char* phone_number, int points, enum user_role role){

    //Checks if username, password and phone_number are strings of acceptable sizes.
    if(strlen(username) > USERNAME_SIZE){
        printf("username cant be bigger than 29 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(password) > USERNAME_SIZE){
        printf("password cant be bigger than 29 characters");
        exit(EXIT_FAILURE);
    }
    if(strlen(phone_number) > 15){
        printf("phone number cant be bigger than 14 characters");
        exit(EXIT_FAILURE);
    }

    //Create the new entry
    struct user new_entry;
    strncpy(new_entry.username, username, USERNAME_SIZE);
    strncpy(new_entry.password, password, USERNAME_SIZE);
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

/**
 * This function is used to update the user file.
 * It clears the file and then writes all users from the global linked list to the file.
 */
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

/**
 * This function is used to get a user by their username.
 * It iterates over the global linked list of users and returns the user with the matching username.
 *
 * @param username The username of the user to be retrieved.
 * @return Returns a pointer to the user if found, NULL otherwise.
 */
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

/**
 * This function is used to delete a user by their username.
 * It iterates over the global linked list of users and removes the user with the matching username.
 * It also updates the user file after the deletion.
 *
 * @param username The username of the user to be deleted.
 * @return Returns 1 if the user was deleted successfully, 0 otherwise.
 */
int delete_user(char username[]){
    struct User_Node* index = users;
    struct User_Node* previous_index = NULL;
    while (index != NULL){
        if (strcmp(index->data.username, username) == 0){

            //Delete all items with username
            struct Item_Node* user_items = get_items_from_user(username);
            while(user_items != NULL){
                delete_bid_username(username);
                delete_item(user_items->data.id);

                struct Item_Node* next_item = user_items->next;
                free(user_items);
                user_items = next_item;
            }

            //Delete user with username
            if(previous_index == NULL){
                users = index->next;
            } else {
                previous_index->next = index->next;
            }
            free(index);
            update_user_file();

            return 1;
        }
        previous_index = index;
        index = index->next;
    }
    return 0;
}

/* - - - - - - - ITEMS - - - - - - - - -*/

// Items [PRIVATE]
/**
 * This function is used to import item data from a file.
 * It reads the file line by line and creates a new item node for each line.
 * Each item node is added to the global linked list of items.
 */
void import_item_file(){

    FILE* file = fopen("items.csv", "r");

    if(file == NULL){
        printf("Couldn't open items.csv");
        exit(EXIT_FAILURE);
    }

    while(!feof(file)){
        struct item i;
        struct timestamp t;

        char username[USERNAME_SIZE];

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

/**
 * This function is used to save an item to a file.
 * It opens the file in append mode and writes the item data to the file.
 *
 * @param i The item to be saved to the file.
 */
void save_item_to_file(struct item i){
    FILE* file = fopen("items.csv", "a"); //Open file in append mode

    fprintf(file, "%d, %s, %s, %s, %s, %d, %d, %d:%d:%d, %d/%d/%d\n", i.id, i.owner->username, i.title, i.description, i.location, i.category, i.quantity, i.timestamp.hour, i.timestamp.minute, i.timestamp.seconds, i.timestamp.day, i.timestamp.month, i.timestamp.year);

    fclose(file); //Close file
}

// Items [PUBLIC]
/**
 * This function is used to print all items.
 * It iterates over the global linked list of items and prints each item's ID, username, title, and description.
 */
void print_items(){

    struct Item_Node* rest_items = items;

    printf("ITEMS:\n");
    while(rest_items != NULL){
        printf("ID: %d, Username: %s, Title: %s, Description: %s \n", rest_items->data.id, rest_items->data.owner->username, rest_items->data.title, rest_items->data.description);
        rest_items = rest_items->next;
    }
    printf("\n");
}

/**
 * This function is used to print all unexpired items.
 * It iterates over the global linked list of items and prints each unexpired item's details.
 */
void print_unexpired_items(){

    struct Item_Node* rest_items = items;

    printf("ITEMS:\n");
    while(rest_items != NULL){

        //Only print unexpired items
        if(cmp_timestamp(timestamp_now(), rest_items->data.timestamp) != -1){
            rest_items = rest_items->next;
            continue;
        }

        char category_string[20];
        switch(rest_items->data.category){
            case(fruit):
                strcpy(category_string, "Fruit");
                break;
            case(meat):
                strcpy(category_string, "Meat");
                break;
            case(vegetable):
                strcpy(category_string, "Vegetable");
                break;
        }

        printf("ID: %d, Username: %s, Title: %s, Description: %s, Category: %s, Auction expiration: ", rest_items->data.id, rest_items->data.owner->username, rest_items->data.title, rest_items->data.description, category_string);

        print_timestamp(rest_items->data.timestamp);

        //Include the highest bid
        struct bid* highest_bid = get_highest_bid(rest_items->data.id);
        if(highest_bid != NULL){
            printf(", Highest bid: %d by %s", highest_bid->amount, highest_bid->user->username);
        }
        printf("\n");

        rest_items = rest_items->next;
    }
    printf("\n");
}

/**
 * This function is used to add a new item.
 * It creates a new item and adds it to the global linked list of items.
 * It also saves the new item to a file.
 *
 * @param seller_name The username of the seller.
 * @param title The title of the item.
 * @param description The description of the item.
 * @param location The location of the item.
 * @param category The category of the item.
 * @param quantity The quantity of the item.
 * @param end_time The end time of the item.
 */
void add_item(char seller_name[], char title[], char description[], char location[], enum item_category category, int quantity, struct timestamp end_time){

    if(strlen(title) > USERNAME_SIZE){
        printf("title can't be longer than USERNAME_SIZE characters");
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
    strncpy(new_item.title, title, USERNAME_SIZE);
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

/**
 * This function is used to update the item file.
 * It clears the file and then writes all items from the global linked list to the file.
 */
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

/**
 * This function is used to get all items from a specific user.
 * It iterates over the global linked list of items and adds each item with the matching username to a new linked list.
 * The new linked list is returned.
 *
 * @param username The username of the user whose items are to be retrieved.
 * @return Returns a linked list of items for the specified user.
 */
struct Item_Node* get_items_from_user(char username[]){
    struct Item_Node* linked_list = NULL;
    struct Item_Node* index = items;
    while(index != NULL){
        if(strcmp(index->data.owner->username, username) == 0){
            struct Item_Node* new_node = (struct Item_Node*) malloc(sizeof(struct Item_Node));
            new_node->data = index->data;
            new_node->next = linked_list;
            linked_list = new_node;
        }
        index = index->next;
    }
    return linked_list;
}

/**
 * This function is used to delete an item by its ID.
 * It iterates over the global linked list of items and removes the item with the matching ID.
 * It also updates the item file after the deletion.
 *
 * @param item_id The ID of the item to be deleted.
 * @return Returns 1 if the item was deleted successfully, 0 otherwise.
 */
int delete_item(int item_id){
    struct Item_Node* index = items;
    struct Item_Node* previous_index = NULL;
    while (index != NULL){
        if (index->data.id == item_id){
            if(previous_index == NULL){
                items = index->next;
            } else {
                previous_index->next = index->next;
            }
            delete_bid_id(item_id);
            free(index);
            update_item_file();
            return 1;
        }
        previous_index = index;
        index = index->next;
    }
    update_item_file();
    return 0;
}

/* - - - - - - - BIDS - - - - - - - - -*/

// Bids [PRIVATE]
/**
 * This function is used to import bid data from a file.
 * It reads the file line by line and creates a new bid for each line.
 * Each bid is added to the global linked list of bids.
 */
void import_bid_file(){

    FILE* file = fopen("bids.csv", "r");

    if(file == NULL){
        printf("Couldn't open bids.csv");
        exit(EXIT_FAILURE);
    }

    while(!feof(file)){
        //Scan line from file
        struct bid* b = (struct bid*)malloc(sizeof(struct bid));
        char username[USERNAME_SIZE];
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

/**
 * This function is used to save a bid to a file.
 * It opens the file in append mode and writes the bid data to the file.
 *
 * @param b The bid to be saved to the file.
 */
void save_bid_to_file(struct bid b){
    FILE* file = fopen("bids.csv", "a"); //Open file in append mode

    fprintf(file, "%d, %s, %d\n", b.item_id, b.user->username, b.amount);

    fclose(file); //Close file
}

// Bids [PUBLIC]
/**
* This function is used to add a bid to an item.
* It first allocates memory for a new bid and checks if the allocation was successful.
* It then sets the item ID, bidder, and bid amount for the new bid.
* The new bid is saved to the bids.csv file.
* A new node is created for the bid and added to the head of the global linked list of bids.
*
* @param item_id The ID of the item on which the bid is being placed.
* @param bidder The user who is placing the bid.
* @param bid_amount The amount of the bid being placed.
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


/**
 * This function is used to get all bids with a specific item ID.
 * It iterates over the global linked list of bids and adds each bid with the matching item ID to a new linked list.
 * The new linked list is returned.
 *
 * @param item_id The ID of the item for which the bids are to be retrieved.
 * @return Returns a linked list of bids for the specified item.
 */
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

/**
 * This function is used to update the bids.csv file.
 * It first clears the file.
 * It then iterates over the global linked list of bids and writes each bid to the file.
 */
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

/**
 * This function is used to print all bids.
 * It iterates over the global linked list of bids and prints the item ID, username of the bidder, and bid amount for each bid.
 */
void print_bids(){
    struct Bid_Node* rest_bids = bids;

    printf("BIDS\n");
    while(rest_bids != NULL){
        printf("%d %s %d\n", rest_bids->data->item_id, rest_bids->data->user->username, rest_bids->data->amount);
        rest_bids = rest_bids->next;
    }
    printf("\n\n");
}

/**
 * This function is used to delete a bid by its item ID.
 * It iterates over the global linked list of bids and removes the bid with the matching item ID.
 * It also updates the bid file and the user file after the deletion.
 *
 * @param item_id The ID of the item for which the bid is to be deleted.
 */
void delete_bid_id(int item_id){
    struct Bid_Node* index = bids;
    struct Bid_Node* previous_index = NULL;
    while (index != NULL){
        if (index->data->item_id == item_id){
            if(previous_index == NULL){
                bids = index->next;
            } else {
                previous_index->next = index->next;
            }

            index->data->user->points += index->data->amount;

            free(index);

            update_bid_file();
            update_user_file();

            delete_bid_id(item_id);
            return;
        }
        previous_index = index;
        index = index->next;
    }
    update_bid_file();
}

/**
 * This function is used to delete a bid by the username of the bidder.
 * It iterates over the global linked list of bids and removes the bid placed by the user with the matching username.
 * It also updates the bid file and the user file after the deletion.
 *
 * @param username The username of the user whose bid is to be deleted.
 */
void delete_bid_username(char username[]){
    struct Bid_Node* index = bids;
    struct Bid_Node* previous_index = NULL;
    while (index != NULL){
        if (strcmp(index->data->user->username, username) == 0){
            if(previous_index == NULL){
                bids = index->next;
            } else {
                previous_index->next = index->next;
            }

            index->data->user->points += index->data->amount;

            free(index);

            update_bid_file();
            update_user_file();

            delete_bid_username(username);
            return;
        }
        previous_index = index;
        index = index->next;
    }
    update_bid_file();
}

/* - - - - - - - GENERAL - - - - - - - - -*/

/**
 * This function is used to load data from CSV files.
 * It calls the functions to import users, items, and bids from their respective CSV files.
 */
void load_data_from_csv(){
    import_user_file();
    import_item_file();
    import_bid_file();
}

