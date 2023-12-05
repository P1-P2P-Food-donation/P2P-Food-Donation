//
// Created by Emil on 27-11-2023.
//

#include "interface.h"

// Function for the login menu
void login_menu_print(char *system_user, enum user_role *user_role) {
    int choice;
    bool is_logged_in = false;

    while (!is_logged_in) {
        printf("[1] Login\n");
        printf("[2] Create user\n");
        printf("[3] Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        // Call the function to handle the action
        is_logged_in = login_menu_helper(choice, system_user, user_role);
    }
}

// Function to handle actions from the login menu
bool login_menu_helper(int choice, char *system_user, enum user_role *user_role) {
    switch (choice) {
        case 1:
            // Login
            return login(system_user, user_role);
        case 2:
            // Create user
            create_user();
            return false;  // User not logged in
        case 3:
            // Exit
            exit(0);
        default:
            printf("Invalid choice\n");
            return false;  // User not logged in
    }
}
