//
// Created by Emil on 16-11-2023.
//

#include "login.h"
#define POINTS_START 100

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
void scanLoginCredentials(char inputUsername[], char inputPassword[]) {
    printf("Enter username: ");
    scanf("%s", inputUsername);
    printf("Enter password: ");
    scanf("%s", inputPassword);
}

// Login menu
void printLoginMenu(char *systemUser) {
    int choice;
    char inputUsername[30];
    char inputPassword[30];
    struct user* loggedInUser;

    printf("[1] Login\n");
    printf("[2] Create user\n");
    printf("[3] Exit\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Login
            printf("Enter username: ");
            scanf("%s", inputUsername);

            loggedInUser = get_user(inputUsername); // Get the user by username
            if (loggedInUser != NULL) {
                int loginStatus = login(loggedInUser, inputUsername, inputPassword);
                if (loginStatus == 1) {
                    printf("Login successful!\n");
                    strcpy(systemUser, inputUsername);  // Copy the username
                } else {
                    printf("Login failed. Invalid credentials.\n");
                }
            } else {
                printf("User not found.\n");
            }
            break;
        case 2:
            // Create user
            createUser();
            break;
        case 3:
            // Exit
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
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

    // Add user to database
    add_user(username, password, phone_number, points, role);
}

// Function to login
int login(struct user* user, char inputUsername[], char inputPassword[]) {
    int loginStatus = 0;

    // Scan login credentials
    scanLoginCredentials(inputUsername, inputPassword);

    // Check credentials
    loginStatus = checkCredentials(user, inputUsername, inputPassword);

    return loginStatus;
}