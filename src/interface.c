//
// Created by Nicolai on 10-12-2023.
//

#include "interface.h"
#include "stdio.h"
#include "database.h"
#include "auction.h"
#include "login.h"

/**
 * This function is used to clear the input buffer.
 * It reads characters from the input buffer until it encounters a newline character ('\n') or the end of file (EOF).
 * This is useful in scenarios where you want to ensure that any leftover characters from previous input operations do not interfere with future input operations.
 */
void clear_input_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * This function is used to print a menu and scan the user's choice.
 * It takes in an array of menu items and the size of the array.
 * Each menu item consists of a string and a function pointer.
 * The function prints each menu item and then scans the user's choice.
 * It then calls the function corresponding to the user's choice.
 *
 * @param menu The array of menu items.
 * @param size The size of the array.
 * @return Returns an integer status code.
 */
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

/**
 * This function is used to scan the ID of an item to be deleted.
 * It then calls the delete_item function with the scanned ID.
 *
 * @return Returns an integer status code.
 */
int delete_item_scan() {
    int id = 0;

    printf("Type the ID of the item you want to delete:\n");
    scanf("%d", &id);

    int delete_item_check = delete_item(id);
    if (delete_item_check){
        printf("Item %d was removed\n", id);
    } else {
        printf("Item %d was not found\n", id);
    }
}

/**
 * This function is used to scan the username of a user to be deleted.
 * It then calls the delete_user function with the scanned username.
 *
 * @return Returns an integer status code.
 */
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

/**
 * This function is used to scan the details of a bid to be placed.
 * It scans the item ID, the bidder, and the bid amount.
 * It then calls the make_bid function with the scanned details.
 *
 * @return Returns an integer status code.
 */
int make_bid_scan() {

    int item_id, bid_amount;

    printf("Enter the item you want to bid on:\n");
    scanf("%d", &item_id);

    struct bid* highest_bid = get_highest_bid(item_id);
    if(highest_bid == NULL){
        printf("No other bid has been placed yet\n");
    } else {
        printf("The current highest bid is %d by %s\n", highest_bid->amount, highest_bid->user->username);
    }

    printf("How much do you want to bid on this item?:\n");
    scanf("%d", &bid_amount);

    make_bid(item_id, current_user, bid_amount);

    return 0;
}

/**
 * This function is used to print all users.
 * It calls the print_users function.
 *
 * @return Returns an integer status code.
 */
int print_all_users(){
    print_users();
    return 0;
}

/**
 * This function is used to print all unexpired items.
 * It calls the print_unexpired_items function.
 *
 * @return Returns an integer status code.
 */
int print_all_unexpired_items(){
    print_unexpired_items();
    return 0;
}

/**
 * This function is used to scan the details of an item to be auctioned.
 * It scans the seller name, title, description, location, category, quantity, and end time.
 * It then calls the add_item function with the scanned details.
 *
 * @return Returns an integer status code.
 */
int auctionise_item_scan(){
    char item_title[30];
    char item_description[100];
    char item_location[100];
    enum item_category category;
    int quantity;
    struct timestamp t;

    printf("Please dont use dots instead of commas and avoid language specific characters\n");

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

/**
 * This function is used to display the points of the current user.
 * The specific implementation depends on the structure of the user.
 *
 * @return Returns an integer status code.
 */
int display_points(){
    printf("You have %d points\n\n", current_user->points);
    return 0;
}

/**
 * This function is used to print the auctions on which the current user has placed bids.
 * It retrieves all items on which the current user has placed bids and iterates over them.
 * For each item, it checks if the auction has ended and if the current user has the highest bid.
 * It then prints the item details along with the auction status and the highest bid details.
 */
void print_bidding_auctions(){
    struct Item_Node* index = get_items_with_bids_by_user(current_user->username);
    printf("Auctions with your bids\n");
    if(index != NULL){
        do{
            //Check if auction has ended
            struct bid* highest_bid = get_highest_bid(index->data.id);
            if(cmp_timestamp(timestamp_now(), index->data.timestamp) == 1){
                if(strcmp(highest_bid->user->username, current_user->username) == 0){
                    printf("(WIN) id: %d, title: %s : You won this auction. Seller '%s' can be contacted with phone-number: %s\n",index->data.id, index->data.title, index->data.owner->username, index->data.owner->phone_number);
                } else {
                    printf("(LOSS) id: %d, title: %s : You lost this auction. Winner was %s with a bid of %d\n",index->data.id, index->data.title, highest_bid->user->username, highest_bid->amount);
                }
            } else {
                printf("(RUNNING) id: %d, title: %s : Highest bid so far is %d from %s\n", index->data.id, index->data.title, highest_bid->amount, highest_bid->user->username);
            }

            index = index->next;
        } while (index != NULL);
    } else {
        printf("*You haven't bid on any items*\n");
    }

}

/**
 * This function is used to print the auctions created by the current user.
 * It retrieves all items created by the current user and iterates over them.
 * For each item, it checks if the auction has ended and if there are any bids.
 * It then prints the item details along with the auction status and the highest bid details.
 */
void print_own_auctions(){
    struct Item_Node* own_auctions = get_items_from_user(current_user->username);
    printf("Your auctions:\n");
    if(own_auctions != NULL){
        do{
            //Check if auction has ended
            if(cmp_timestamp(timestamp_now(), own_auctions->data.timestamp) == 1){
                printf("(ENDED) id: %d, title: %s : ", own_auctions->data.id, own_auctions->data.title);
                struct bid* b = get_highest_bid(own_auctions->data.id);
                //Check if any user have placed a bet
                if(b == NULL){
                    printf("this auction ended without any bidders\n");
                } else {
                    printf("%s placed the highest bid of %d, their phone-number is %s\n", b->user->username, b->amount, b->user->phone_number);
                }
            } else {
                printf("(RUNNING) id: %d, title: %s : ", own_auctions->data.id, own_auctions->data.title);

                struct bid* b = get_highest_bid(own_auctions->data.id);
                if(b == NULL){
                    printf("this auction has no bidders yet\n");
                } else {
                    printf("highest bid is %d by user: %s\n", b->amount, b->user->username);
                }
            }
            own_auctions = own_auctions->next;
        }while(own_auctions != NULL);
        free(own_auctions);
    } else {
        printf("*You don't have any auctions*\n");
    }
}

/**
 * This function is used to print the auctions and bids of the current user.
 * The specific implementation depends on the structure of the auctions and bids.
 *
 * @return Returns an integer status code.
 */
int my_auction_and_bids(){

    update_claim_status();
    print_own_auctions();
    printf("\n");
    print_bidding_auctions();
    printf("\n");

    return 0;
}
