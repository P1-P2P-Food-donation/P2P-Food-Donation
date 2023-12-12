//
// Created by nicol on 27-11-2023.
//

#include "buy_and_sell.h"
#include "login.h"

#include <stdio.h>



int sell_food() {
    char* title;
    char* location;
    char description[5];
    int quantity = 1;

    printf("Write the title of your product:\n");
    scanf("%s", title);

    printf("Write the description of your product:\n");
    scanf("%s", description);

    printf("Write the description of your product:\n");
    scanf("%s", location);

    printf("Write the quantity of your product:\n");
    scanf("%d", &quantity);

    enum item_category category;

    printf("Select the category of your product:\n");
    for (int i = fruit; i < meat; i++ ) {
        switch (i) {
            case fruit:
                printf("%d: Fruit", i);
                break;
            case vegetable:
                printf("%d: Vegetable", i);
            case meat:
                printf("%d: Meat", i);
            default:
                break;
        }
    }
    int selected = 0;
    scanf("%i", &selected);
    switch (selected) {
        case fruit:
            category = fruit;
            break;
        case vegetable:
            category = vegetable;
            break;
        case meat:
            category = meat;
        default:
            break;
    }

    add_item(current_user->username, title, description, location, category, quantity, timestamp_now());
    return 0;
}

int buy_food() {
    int id;

    print_items();

    printf("Write the id of the food you want to buy:\n");
    scanf("%d", &id);

    delete_item(id);
    return 0;
}
