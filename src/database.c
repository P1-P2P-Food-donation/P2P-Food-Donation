//
// Created by feddersen on 16/11/2023.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <time.h>

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

// Timestamp

struct timestamp timestamp_now(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year + 1900; //tm.tm_year is years since 1900
    int month = tm.tm_mon + 1; //Years are zero-based
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int minute = tm.tm_min;
    int second = tm.tm_sec;

    struct date temp_date = {year, month, day};
    struct timestamp temp_timestamp = {temp_date, hour, minute, second};
    return temp_timestamp;
}

struct timestamp create_timestamp(int second, int minute, int hour, int day, int month, int year){
    struct date d = {year, month, day};
    struct timestamp t = {d, hour, minute, second};
    return t;
}

void print_timestamp(struct timestamp timestamp){
    printf("Timestamp: %02d:%02d:%02d %02d/%02d/%04d\n", timestamp.hour, timestamp.minute, timestamp.seconds, timestamp.date.day, timestamp.date.month, timestamp.date.year);
}

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

    while(rest_users != NULL){
        printf("User: %s\n", rest_users->data.username);
        rest_users = rest_users->next;
    }
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
        struct date d;
        struct timestamp t;

        char username[30];

        int success_amount = fscanf(file, "%d, %[^,], %[^,], %[^,], %[^,], %d, %d, %d:%d:%d, %d/%d/%d\n", &i.id, username, i.title, i.description, i.location, &i.category, &i.quantity, &t.hour, &t.minute, &t.seconds, &d.day, &d.month, &d.year);
        if(success_amount != 13){
            printf("Error importing items.csv, %d", success_amount);
            exit(EXIT_FAILURE);
        }
        t.date = d;
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

    fprintf(file, "%d, %s, %s, %s, %s, %d, %d, %d:%d:%d, %d/%d/%d\n", i.id, i.owner->username, i.title, i.description, i.location, i.category, i.quantity, i.timestamp.hour, i.timestamp.minute, i.timestamp.seconds, i.timestamp.date.day, i.timestamp.date.month, i.timestamp.date.year);

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

void add_item(char seller_name[], char title[], char description[], char location[], enum item_category category, int quantity){

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
    new_item.timestamp = timestamp_now();
    strncpy(new_item.title, title, 30);
    strncpy(new_item.description, description, 100);
    strncpy(new_item.location, location, 100);
    new_item.category = category;
    new_item.quantity = quantity;

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

// General

void load_data_from_csv(){
    import_user_file();
    import_item_file();
}
