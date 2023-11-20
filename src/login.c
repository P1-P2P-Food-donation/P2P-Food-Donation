//
// Created by Emil on 17-11-2023.
//

#include "login.h"

// Check login credentials
int checkCredentials(struct user* user, char inputUsername[], char inputPassword[]) {
    // Compare input with user struct values
    if (strcmp(inputUsername, user->username) == 0 && strcmp(inputPassword, user->password) == 0) {
        return 1;  // Login successful
    } else {
        return 0;  // Login failed
    }
}

// Scan login credentials
void scanLoginCredentials(char inputPassword[], char inputUsername[]) {
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);
}


// Login menu
void printLoginMenu(char *systemUser, enum user_role *userRole) {
    int choice;
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        printf("[1] Login\n");
        printf("[2] Create user\n");
        printf("[3] Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        // Call the function to handle the action
        isLoggedIn = actionLoginMenu(choice, systemUser, userRole);
    }
}


// Handle actions from the login menu
bool actionLoginMenu(int choice, char *systemUser, enum user_role *userRole) {
    switch (choice) {
        case 1:
            // Login
            return login(systemUser, userRole);
        case 2:
            // Create user
            createUser();
            return false;  // User not logged in
        case 3:
            // Exit
            exit(0);
        default:
            printf("Invalid choice\n");
            return false;  // User not logged in
    }
}

// Make a new user
void createUser() {
    char username[30];
    char password[30];
    char phone_number[15];
    int points = POINTS_START;
    enum user_role role = role_user;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter phone number: ");
    scanf("%s", phone_number);

    // Add user to the database
    add_user(username, password, phone_number, points, role);
}

// Function to login
bool login(char *systemUser, enum user_role *userRole) {
    char inputUsername[30];
    char inputPassword[30];
    struct user *loggedInUser;

    // Scan login credentials
    scanLoginCredentials(inputPassword, inputUsername);

    // Get the user by username
    loggedInUser = get_user(inputUsername);

    if (loggedInUser != NULL) {
        int loginStatus = checkCredentials(loggedInUser, inputUsername, inputPassword);
        if (loginStatus == 1) {
            printf("Login successful!\n");
            strcpy(systemUser, inputUsername);  // Copy the username
            *userRole = loggedInUser->role;    // Copy the user role
            return true;  // User logged in
        } else {
            printf("Login failed. Invalid credentials.\n"); // wrong password
        }
    } else {
        printf("No user with the username: %s was found\n", inputUsername); // User not found
    }

    return false;  // User not logged in
}