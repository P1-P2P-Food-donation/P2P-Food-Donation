//
// Created by Emil on 17-11-2023.
//
#ifndef P2P_FOOD_DONATION_LOGIN_H
#define P2P_FOOD_DONATION_LOGIN_H

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POINTS_START 100

// Defining boolean values
typedef enum {
    false,
    true
} bool;


// Declaring functions
int check_credentials(struct user* user, char input_username[], char input_password[]);
void scan_login_credentials(char input_password[], char input_username[]);
void create_user();
bool login(char *system_user, enum user_role *user_role);

#endif // P2P_FOOD_DONATION_LOGIN_H