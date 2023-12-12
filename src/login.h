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

extern struct user* current_user;

// Defining boolean values
typedef enum {
    false,
    true
} bool;

// Declaring functions
int check_credentials(struct user* user, char input_username[], char input_password[]);
void scan_login_credentials(char input_password[], char input_username[]);
int create_user();
int login();

#endif // P2P_FOOD_DONATION_LOGIN_H