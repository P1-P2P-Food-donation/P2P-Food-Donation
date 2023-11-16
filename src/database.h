//
// Created by feddersen on 16/11/2023.
//

#ifndef P2P_FOOD_DONATION_DATABASE_H
#define P2P_FOOD_DONATION_DATABASE_H

#endif //P2P_FOOD_DONATION_DATABASE_H

enum user_role{role_admin, role_user};

struct user{
    char username[30];
    char password[30];
    char phone_number[15];
    int points;
    enum user_role role;
};

void add_user(char* username, char* password, char* phone_number, int points, enum user_role role);
struct user* get_user(char* username);
void print_users();