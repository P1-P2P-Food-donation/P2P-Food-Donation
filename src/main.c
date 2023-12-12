//
// Created by feddersen on 14/11/2023.
//

#include "interface.h"
#include "input_data.h"
#include <string.h>
#include "userpanel.h"


int main(void){

    const int menu_size = 3;
    struct Menu *user_panel = create_userpanel();

    printscan_menu(user_panel, 2);



    char system_user[30];
    enum user_role user_role; // user=1 admin=0

    read_data();
    print_items();
    print_users();
    add_user("Victor", "Password", "88888888", 100, role_user);

    login_menu_print(system_user, &user_role);
    //printf("%s", systemUser);
    //printf("%d", userRole);

    /*
    Adding a user:
        add_user("Victor", "Password", "88888888", 100, role_user);
    Reading and writing attributes:
        struct user* user = get_user("Victor");
        printf("%s", user->username);
        strcpy(user->username, "Anton");
    Printing all users:
        print_users();
     */
    return 0;
}
