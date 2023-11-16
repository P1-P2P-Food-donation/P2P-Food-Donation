//
// Created by feddersen on 16/11/2023.
//
#include "database.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

struct user* users = {};
int users_size = 0;

struct user get_user(char* username){
    for (int i = 0; i < users_size; ++i) {
        if(strcmp(users[i].username, username) == 0 ){
            return users[i];
        }
    }
    printf("No user with the username: %s was found", username);
    exit(EXIT_FAILURE);
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