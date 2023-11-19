//
// Created by Emil on 16-11-2023.
//
#ifndef P2P_FOOD_DONATION_LOGIN_H
#define P2P_FOOD_DONATION_LOGIN_H

#endif //P2P_FOOD_DONATION_LOGIN_H

#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POINTS_START 100

int login(struct user* user, char inputUsername[], char inputPassword[]);
int checkCredentials(struct user* user, char inputUsername[], char inputPassword[]);
void scanLoginCredentials(char inputUsername[], char inputPassword[]);
void printLoginMenu(char *systemUser, enum user_role *userRole);
void createUser();
void actionLoginMenu(int choice, char *systemUser, enum user_role *userRole, int *count);

