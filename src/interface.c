//
// Created by Nicolai on 10-12-2023.
//

#include "interface.h"
#include "stdio.h"
#include "database.h"
#include "auction.h"
#include "login.h"

void clear_input_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int printscan_menu(struct menu_item menu[], int size) {
    int valid_choice;
    do {
        int valg;

        for (int i = 0; i < size; i++) {
            printf("[%d] %s\n", i+1, menu[i].string);
        }
        printf("[%d] Exit\n\n", size + 1);

        scanf("%d", &valg);

        valid_choice = (valg >= 1 && valg <= size);

        if (valid_choice) {
            if(menu[valg-1].function()){
                return 0;
            };

        } else if (valg == size + 1){
            return 1;
        }
        else {
            printf("Invalid choice! Try again\n");
        }
    } while (1);
}

int delete_item_scan() {
    int id = 0;

    printf("Type the ID of the item you want to delete:\n");
    scanf("%d", &id);

    return delete_item(id);
}

int delete_user_scan() {
    char username[USERNAME_SIZE];

    printf("Type the username you want to delete:\n");
    scanf("%s", username);

    int delete_user_check = delete_user(username);
    if (delete_user_check) {
        printf("User %s was removed\n", username);
    } else {
        printf("User %s does not exist!\n", username);
    }
    return 0;
}

int make_bid_scan() {

    int item_id, bid_amount;

    printf("Enter the item you want to bid on:\n");
    scanf("%d", &item_id);

    printf("Enter the bid amount:\n");
    scanf("%d", &bid_amount);

    //make_bid(item_id, current_user, bid_amount);
}

int auctionise_item_scan(){
    char item_title[30];
    char item_description[100];
    char item_location[100];
    enum item_category category;
    int quantity;
    struct timestamp t;

    clear_input_buffer();
    printf("Item title: ");
    scanf("%[^\n]", item_title);
    clear_input_buffer();
    printf("\nItem description: ");
    scanf("%[^\n]", item_description);
    clear_input_buffer();
    printf("\nItem location: ");
    scanf("%[^\n]", item_location);
    clear_input_buffer();
    printf("\nCategory([1]fruit, [2]vegetable, [3]meat): ");
    scanf("%d", &category);
    printf("\nQuantity: ");
    scanf("%d", &quantity);
    t = timestamp_delta(6 * 60 * 60); //Set auction expiration to 6 hours from now
    add_item(current_user->username, item_title, item_description, item_location, category - 1, quantity, t);

    printf("\nYour item has been added to the auction. The auction wil expire in 6 hours\n");
    return 0;
}