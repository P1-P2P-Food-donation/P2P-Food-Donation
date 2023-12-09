//
// Created by feddersen on 16/11/2023.
//

#ifndef P2P_FOOD_DONATION_DATABASE_H
#define P2P_FOOD_DONATION_DATABASE_H

#endif //P2P_FOOD_DONATION_DATABASE_H

enum user_role{role_admin, role_user};
enum item_category{fruit, vegetable, meat};

struct date{
    int year;
    int month;
    int day;
};

struct timestamp{
    struct date date;
    int hour;
    int minute;
    int seconds;
};

struct bid{
    int id;
    struct user* user;
    struct timestamp timestamp;
    int amount;
};

struct user{
    char username[30];
    char password[30];
    char phone_number[15];
    int points;
    enum user_role role;
};

struct item{
    int id;
    struct user* owner;
    struct timestamp timestamp;
    char title[30];
    char description[100];
    char location[100];
    enum item_category category;
    int quantity;
};



//Timestamp
struct timestamp timestamp_now();
struct timestamp create_timestamp(int second, int minute, int hour, int day, int month, int year);
void print_timestamp(struct timestamp timestamp);

//Items
void print_items();
void add_item(char username[], char title[], char description[], char location[], enum item_category category, int quantity);
void update_item_file();

//Users
void print_users();
void add_user(char* username, char* password, char* phone_number, int points, enum user_role role);
struct user* get_user(char* username);
void update_user_file();


//General
void load_data_from_csv();