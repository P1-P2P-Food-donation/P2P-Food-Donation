//
// Created by Emil on 11-12-2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "database.h"
#include "string.h"
#include "input_data.h"
void input_data(){
    input_users();
    input_items();
}
void input_items(){
    char username[30];
    char title[30];
    char description[100];
    char location[100];
    char category[30];
    int quantity;
    openfile("items.txt");
    while(fscanf(file, "%s,%s,%s,%s,%s,%d", username, title, description, location, &category, quantity) != EOF){
        add_item(username, title, description, location, category, quantity);
    }
    closefile();
}
void input_users(){
    char username[30];
    char password[30];
    char phone_number[15];
    int points;
    char user_role[30];
    openfile("users.txt");
    while(fscanf(file, "%s %s %s %d %d", username, password, phone_number, &points, &role) != EOF){
        add_user(username, password, phone_number, points, role);
    }
    closefile();
}