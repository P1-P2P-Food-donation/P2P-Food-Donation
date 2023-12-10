//
// Created by Jeppe Nyland Mortensen on 29/11/2023.
//

#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"
#include "interface.h"


struct Menu* create_userpanel() {
    struct Menu *user_panel = malloc(2 * sizeof(struct Menu));
    if (user_panel == NULL) {
        printf("Out of memory!");
        return NULL;
    }

    struct Menu menu1, menu2;

    menu1.string = "Login";
    menu1.function = &printMessage;
    user_panel[0] = menu1;

    menu2.string = "Create user";
    menu2.function = &printMessage;
    user_panel[1] = menu2;

    return user_panel;
}



