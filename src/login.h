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
int checkCredentials(struct user* user, char inputUsername[], char inputPassword[]);
void scanLoginCredentials(char inputPassword[], char inputUsername[]);
void printLoginMenu(char *systemUser, enum user_role *userRole);
void createUser();
bool actionLoginMenu(int choice, char *systemUser, enum user_role *userRole);
bool login(char *systemUser, enum user_role *userRole);

#endif // P2P_FOOD_DONATION_LOGIN_H