//
// Created by feddersen on 16/11/2023.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <time.h>

struct user* users = {};
struct item* items = {};

int users_size = 0;
int items_size = 0;

struct timestamp timestamp_now(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year + 1900; //Years since 1900
    int month = tm.tm_mon + 1; //Years are zero-based
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int minute = tm.tm_min;
    int second = tm.tm_sec;

    struct date temp_date = {year, month, day};
    struct timestamp temp_timestamp = {temp_date, hour, minute, second};
    return temp_timestamp;
}

void print_timestamp(struct timestamp timestamp){
    printf("Current date and time: %04d-%02d-%02d %02d:%02d:%02d\n", timestamp.date.year, timestamp.date.month, timestamp.date.day, timestamp.hour, timestamp.minute, timestamp.seconds);
}

struct user* get_user(char* username){
    for (int i = 0; i < users_size; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    //printf("No user with the username: %s was found", username);
    return NULL; // changed from exit(EXIT_FAILURE);
}

void print_users(){
    for (int i = 0; i < users_size; ++i) {
        printf("%s\n", users[i].username);
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

    //Allocate memory for a new user array which is 1 bigger than the last.
    struct user* updated_users = (struct user*)malloc(sizeof(struct user)*(users_size + 1));
    if(updated_users == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }
    //Copy the items of an old user array to a new.
    for (int i = 0; i < users_size; ++i) {
        updated_users[i] = users[i];
    }
    //Create the new entry
    struct user new_entry;
    strncpy(new_entry.username, username, 30);
    strncpy(new_entry.password, password, 30);
    strncpy(new_entry.phone_number, phone_number, 15);
    new_entry.points = points;
    new_entry.role = role;
    updated_users[users_size] = new_entry;

    //Free the memory of the last array
    if(users_size > 0){
        free(users);
    }

    //Set the array to the new and updated array and increment the size.
    users = updated_users;
    users_size++;
}

int get_items_amount(){
    return items_size;
}

struct item* get_items(){
    return items;
}

void add_item(char username[], char title[], char description[], char location[], enum item_category category, int quantity){

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

    //Allocate memory for a new items array which is 1 bigger than the last.
    struct item* updated_items = (struct item*)malloc(sizeof(struct item)*(items_size + 1));
    if(updated_items == NULL){
        printf("Out of memory");
        exit(EXIT_FAILURE);
    }
    //Copy the items of the old array to the new
    for (int i = 0; i < items_size; ++i) {
        updated_items[i] = items[i];
    }
    //Initialize the new item.
    struct item new_item;
    new_item.id = items_size;
    new_item.owner = get_user(username);
    new_item.timestamp = timestamp_now();
    strncpy(new_item.title, title, 30);
    strncpy(new_item.description, description, 100);
    strncpy(new_item.location, location, 100);
    new_item.category = category;
    new_item.quantity = quantity;
    new_item.bid_amount = 0;
    updated_items[items_size] = new_item;

    //Free the memory of the last array
    if(items_size > 0){
        free(items);
    }

    //Set the array to the new and updated array and increment the size.
    items = updated_items;
    items_size++;
}

void print_items(){
    for (int i = 0; i < items_size; ++i) {
        printf("%s\n", items[i].title);
    }
}