//
// Created by Emil on 11-12-2023.
//
#ifndef P2P_FOOD_DONATION_INPUT_DATA_H
#define P2P_FOOD_DONATION_INPUT_DATA_H

void read_data();
FILE* openfile(const char *filename);
enum user_role role_from_string(const char *role_str);
void read_and_add_users();
enum item_category category_from_string(const char *category_str);
void read_and_add_items();

#endif //P2P_FOOD_DONATION_INPUT_DATA_H