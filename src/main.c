//
// Created by feddersen on 14/11/2023.
//

#include "interface.h"
#include <string.h>

int main(void){

    struct Menu menu1, menu2;
    struct Menu menu_list[2];

    int valg = 0;

    menu1.string = "Test";
    menu1.function = &printMessage;
    menu_list[0] = menu1;

    menu2.string = "Test";
    menu2.function = &printMessage;
    menu_list[1] = menu2;

    for (int i = 1; i <= 2; i++) {
        printf("[%d] %s\n", i, menu_list[i-1].string);
    }
    scanf("%d", &valg);

    menu_list[valg-1].function();

    char system_user[30];
    enum user_role user_role; // user=1 admin=0
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
