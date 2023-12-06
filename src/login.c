//
// Created by Emil on 17-11-2023.
//

#include "login.h"

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
void create_user() {
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

// Function to handle the login process
bool login(char *system_user, enum user_role *user_role) {
    char input_username[30];
    char input_password[30];
    struct user *logged_in_user;

    // Scan login credentials
    scan_login_credentials(input_password, input_username);

    // Get the user by username
    logged_in_user = get_user(input_username);

    if (logged_in_user != NULL) {
        int login_status = check_credentials(logged_in_user, input_username, input_password);
        if (login_status == 1) {
            printf("Login successful!\n");
            strcpy(system_user, input_username);  // Copy the username
            *user_role = logged_in_user->role;    // Copy the user role
            return true;  // User logged in
        } else {
            printf("Login failed. Invalid credentials.\n"); // wrong password
        }
    } else {
        printf("No user with the username: %s was found\n", input_username); // User not found
    }

    return false;  // User not logged in
}