//
// Created by feddersen on 14/11/2023.
//
#include "login.h"
#include <string.h>

int main(void){
    char systemUser[30];
    enum user_role userRole; // user=1 admin=0
    add_user("Victor", "Password", "88888888", 100, role_user);
    printLoginMenu(systemUser, &userRole);
    //printf("%s", systemUser);
    //printf("%d", userRole);

    /*
    Adding a user:
        add_user("Victor", "Password", "88888888", 100, role_user);
    Reading and writing attributes
        struct user* user = get_user("Victor");
        printf("%s", user->username);
        strcpy(user->username, "Anton");
    Printing all users:
        print_users();
     */
    return 0;
}
