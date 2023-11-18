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

int login(struct user* user, char inputUsername[], char inputPassword[]);
int checkCredentials(struct user* user, char inputUsername[], char inputPassword[]);
void scanLoginCredentials(char inputUsername[], char inputPassword[]);
void printLoginMenu(char *systemUser);
void createUser();

