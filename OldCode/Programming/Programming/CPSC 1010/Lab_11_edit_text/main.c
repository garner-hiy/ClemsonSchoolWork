#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(void){
    char userstring[250];

    printf("Enter a sample text:\n\n");
    fgets(userstring, 250, stdin);
    //used to remove the newline with a NULL
    if(userstring[strlen(userstring) - 1 ] == '\n'){//This is for fgets
        userstring[strlen(userstring) - 1] = '\0';
    }
    printf("You entered: %s\n\n", userstring);

    char userChar;//used by user to chose a menu option
    PrintMenu();//inital print
    while (userChar != 'q'){//loops through the menu options
        printf("Choose an option:\n");
        scanf(" %c", &userChar);
        if(userChar == 'c' || userChar == 'w' || userChar == 'f' || userChar == 'r' || userChar == 's'){          
            ExecuteMenu(userChar, userstring);
            PrintMenu();//prints the menu
        }
        
    }
    
    return 0;
}