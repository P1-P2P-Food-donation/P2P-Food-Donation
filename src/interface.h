//
// Created by Emil on 27-11-2023.
//

#ifndef P2P_FOOD_DONATION_INTERFACE_H
#define P2P_FOOD_DONATION_INTERFACE_H

#include "login.h"

void login_menu_print(char *system_user, enum user_role *user_role);
bool login_menu_helper(int choice, char *system_user, enum user_role *user_role);

#endif //P2P_FOOD_DONATION_INTERFACE_H