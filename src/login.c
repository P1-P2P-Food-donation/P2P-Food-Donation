//
// Created by Emil on 17-11-2023.
//

#include "login.h"

struct user* current_user = NULL;

// Function to check login credentials
int check_credentials(struct user* user, char input_username[], char input_password[]) {
    // Compare input with user struct values
    if (strcmp(input_username, user->username) == 0 && strcmp(input_password, user->password) == 0) {
        return 1;  // Login successful
    } else {
        return 0;  // Login failed
    }
}

// Function to scan login credentials
void scan_login_credentials(char input_password[], char input_username[]) {
    printf("Enter username: ");
    scanf("%s", input_username);
    printf("Enter password: ");
    scanf("%s", input_password);
}

// Function to create a new user
int create_user() {
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

    if(get_user(username) != NULL){
        printf("A user with that username already exist. Try again\n");
        return 0;
    }

    // Add user to the database
    add_user(username, password, phone_number, points, role);

    current_user = get_user(username);
    return 1;
}

// Function to handle the login process
int login() {
    char input_username[30];
    char input_password[30];

    // Scan login credentials
    scan_login_credentials(input_password, input_username);

    // Get the user by username
    struct user* u = get_user(input_username);

    if(u != NULL){
        if (strcmp(u->password, input_password) == 0){
            current_user = u;
            printf("Login successful!\n");
            return 1;
        }
    }

    printf("Login failed. Invalid credentials.\n"); // wrong username or password
    return 0;

}