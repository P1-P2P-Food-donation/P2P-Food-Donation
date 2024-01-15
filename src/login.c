//
// Created by Emil on 17-11-2023.
//

#include "login.h"

struct user* current_user = NULL;

/**
 * This function is used to check the login credentials of a user.
 * It compares the input username and password with the username and password of the user.
 *
 * @param user The user whose credentials are to be checked.
 * @param input_username The input username to be checked.
 * @param input_password The input password to be checked.
 * @return Returns 1 if the login credentials are correct, 0 otherwise.
 */
int check_credentials(struct user* user, char input_username[], char input_password[]) {
    // Compare input with user struct values
    if (strcmp(input_username, user->username) == 0 && strcmp(input_password, user->password) == 0) {
        return 1;  // Login successful
    } else {
        return 0;  // Login failed
    }
}

/**
 * This function is used to scan the login credentials from the user.
 * It prompts the user to enter their username and password and stores them in the provided variables.
 *
 * @param input_password The variable in which to store the input password.
 * @param input_username The variable in which to store the input username.
 */
void scan_login_credentials(char input_password[], char input_username[]) {
    printf("Enter username: \n");
    scanf("%s", input_username);
    printf("Enter password: \n");
    scanf("%s", input_password);
}

/**
 * This function is used to create a new user.
 * It prompts the user to enter their username, password, and phone number.
 * It then adds the new user to the database and sets them as the current user.
 *
 * @return Returns 1 if the user was created successfully, 0 otherwise.
 */
int create_user() {
    char username[30];
    char password[30];
    char phone_number[15];
    int points = POINTS_START;
    enum user_role role = role_user;

    printf("Enter username:\n");
    scanf("%s", username);
    printf("Enter password:\n");
    scanf("%s", password);
    printf("Enter phone number:\n");
    scanf("%s", phone_number);

    if(get_user(username) != NULL){
        printf("A user with that username already exist. Try again\n");
        return 0;
    }

    // Add user to the database
    add_user(username, password, phone_number, points, role);

    printf("User registered successfully\n\n");
    current_user = get_user(username);
    return 1;
}

/**
 * This function is used to handle the login process.
 * It prompts the user to enter their login credentials and checks them against the database.
 * If the login credentials are correct, it sets the user as the current user.
 *
 * @return Returns 1 if the login was successful, 0 otherwise.
 */
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