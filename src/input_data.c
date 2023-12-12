//
// Created by Emil on 11-12-2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "input_data.h"
#include "database.h"

void read_data(){
    read_and_add_users();
    read_and_add_items();
}

FILE* openfile(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

enum user_role role_from_string(const char *role_str) {
    if (strcmp(role_str, "role_user") == 0) {
        return role_user;
    } else if (strcmp(role_str, "role_admin") == 0) {
        return role_admin;
    }
    // Add more conditions as needed
    return role_user; // Default to ROLE_USER if unknown
}

void read_and_add_users() {
    FILE* file = openfile("users");

    char line[256]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        char *phone_number = strtok(NULL, ",");
        int points = atoi(strtok(NULL, ","));
        char *role_str = strtok(NULL, ",");

        // Convert role string to enum value
        enum user_role role = role_from_string(role_str);

        // Call the add_user function
        add_user(username, password, phone_number, points, role);
    }

    fclose(file);
}

enum item_category category_from_string(const char *category_str) {
    if (strcmp(category_str, "fruit") == 0) {
        return fruit;
    } else if (strcmp(category_str, "vegetable") == 0) {
        return vegetable;
    }
    // Add more conditions as needed
    return fruit; // Default to FRUIT if unknown
}
/*
void read_and_add_items() {
    FILE* file = openfile("items");

    char line[256]; // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line
        char *username = strtok(line, ",");
        char *title = strtok(NULL, ",");
        char *description = strtok(NULL, ",");
        char *location = strtok(NULL, ",");
        char *category_str = strtok(NULL, ",");
        int quantity = atoi(strtok(NULL, ","));

        // Convert category string to enum value
        enum item_category category = category_from_string(category_str);

        // Call the add_item function
        add_item(username, title, description, location, category, quantity);
    }

    fclose(file);
}
 */