# P2P-Food-Donation

## Compiling of program for Windows

### GCC Compiler
First step in compiling the program is making sure you have a compiler for C installed, this can be done by opening power shell and typing in gcc. If the command is not known by the system, there are no compiler installed. A guide to how to install a GCC compiler are provided in this [link]( https://www.youtube.com/watch?v=GxFiUEO_3zM&ab_channel=SavvyNik)

### Compiling
First thing to do to compile the program is moving power shell into the correct directory and this is done with the command cd followed by path to the directory, it shall be the src directory that be linked to. This could look like this "cd R:\ClionProjects\P2P-Food-Donation\src"

After the correct directory is linked to, the following command is used "gcc -o main main.c auction.c database.c interface.c login.c timestamp.c userpanel.c" this command will compile the program into a .exe program with the name main.exe.

Next step is to move the program by dragging it or copying it into another directory with the data files, this can easily be done by moving the .exe program into the directory "data" that is provided in the directory P2P-Food-Donation

After this the program shall be ready to launched by double clicking on it in the data directory.

## Menus
The menus of the program will be displayed as seen below.

[1] Auction menu

[2] List users

[3] Delete a user

[4] Delete a item

[5] Exit

To enter the next menu or action you will need to write the corresponding number and press enter. this means to enter the auction menu you need to press 1 and then enter. The last option in all menus is always Exit and will close the program.
When you need to input data into the program, it will look like the following, that are taken from Auction item:

Please use dots instead of commas and avoid language specific characters

Item title:<span style="color:lightgreen;">Potato</span>

Item description:<span style="color:lightgreen;">Good old Potato</span>

Item location:<span style="color:lightgreen;">Aalborgvej 34</span>

Category([1]fruit, [2]vegetable, [3]meat, [4]leftovers, [5]dairy, [6]other):<span style="color:lightgreen;">2</span>

Quantity:<span style="color:lightgreen;">15</span>

In this menu you will be represented with a prompt ending with semicolon and after the semicolon you will need to write your answer to the prompt and press enter to go to the next one. When entering data into the program it does not work with language specific characters and the program does not work with commas so, please use dots instead. As seen in the category section above you will be required to enter a number corresponding to the category you would like to enter. 

## Important information
### Language specific characters
The program does not work with language specific characters, an example on these could be the Danish “æ, ø, å” so please restrain from using them.

### Commas
As well does the program does not work the commas so, please use dots instead, this is because of the way the data structure is set up and the program will save the data you input to the program wrong if there are any use of commas. 

### Item ID
When trying to bid on an item the program asks for the ID of the item you would like to bid on, this ID can be found under the menu “List items”, the program does not handle it well if you input anything else here then a number. 
## Users available from the start of the program
The program has 2 types of users, and these are admins and users, below are provided a username and password for each type of user. When entering the username and password the program is upper and lower case sensitive.

| Username | Password | User Role |
|----------|----------|-----------|
| Victor   | Password | Admin     |
| Gee      | Louise   | User      |
