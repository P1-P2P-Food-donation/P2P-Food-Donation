//
// Created by feddersen on 16/11/2023.
//
/*
 *
 *  add_user("Victor", "Password", "88888888", 100, role_user);
    add_user("Admin", "Hallu", "88888888", 100, role_admin);
    print_users();
    add_user("Gee", "Louise", "276482", 400, role_user);
    print_users();
 */

#include "stdio.h"
#include "assert.h"
#include "auction.h"

void test_add_user(){
    add_user("Victor", "Password", "88888888", 100, role_user);
    add_user("Admin", "Hallo", "88888888", 100, role_admin);
    add_user("Gee", "Louise", "276482", 400, role_user);
}

void test_print_users(){
    print_users();
}

void test_get_user(){
    struct user u = *get_user("Victor");
    printf("%s, %s", u.username, u.password);

    assert(get_user("Hannah") == NULL);
}

void test_save_user(){
    //save_users();
}

int main(){
    //print_timestamp(create_timestamp(11,12,13,14,12,1990));
    /*
    load_data_from_csv();
    print_users();
    print_bids();
    printf("Call result: %d\n", make_bid(2, get_user("Victor"), 50));
    print_users();
    print_bids();
     */



    load_data_from_csv();

    print_users();
    print_items();
    print_bids();
    //printf("Return: %d\n", delete_user("Victor"));

}

