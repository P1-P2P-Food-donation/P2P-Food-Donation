//
// Created by Jeppe Nyland Mortensen on 29/11/2023.
//

#include "stdbool.h"
#include "stddef.h"
#include "stdio.h"

char* username;

// Interface til brugerpanel
void open_interface() {

    //checks if logged in
    if (username == NULL){
        int choice = -1;

        // A do-while loop that allows users to pick a "menu" through a switch
        do {
            printf("Choose one of the categories:\n");
            printf("1: Log in menu\n"
                   "2: INSERT SOMETHING\n"
                   "3: INSERT SOMETHING\n"
                   "4: INSERT SOMETHING\n");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    //open login menu
                    break;
                case 2:
                    //open another menu
                    break;
                case 3:
                    //open another menu
                    break;
                case 4:
                    //open another menu
                    break;
                default:
                    choice = -1;
                    printf("This choice is not recognized!\n");
                    break;

            }

        } while (choice == -1);

    }
    else {
        //If you are NOT logged in

        int choice = -1;

        // A do-while loop that allows users to pick a "menu" through a switch
        do {
            printf("Choose one of the categories:\n");
            printf("1: Log in menu\n"
                   "2: INSERT SOMETHING\n"
                   "3: INSERT SOMETHING\n"
                   "4: INSERT SOMETHING\n");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    //
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                default:
                    choice = -1;
                    printf("This choice is not recognized!\n");
                    break;

            }

        } while (choice == -1);
    }


}


