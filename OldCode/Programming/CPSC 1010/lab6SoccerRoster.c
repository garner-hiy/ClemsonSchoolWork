/*AJ Garner
Lab Section 1
Lindsey Kirtley, Ashley Moody, Davis Little*/

#include <stdio.h>
#include <string.h>

int main (void){
    char userOption = 'b';//variable used to interact with menu
    int numPlayers;//number of players to input

    printf("How many players to enter: \n");
    scanf("%d", &numPlayers);
    int jerseyNum[numPlayers];   //need to declare after number of players to input
    int playerRating[numPlayers];//need to declare after number of players to input    
    for (int i = 0; i < numPlayers; ++i){//this loop allows user to fill the arrays
        printf("Enter player %d's jersey number:\n", i + 1);//i + 1 is needed to prompt correct order
        scanf("%d", &jerseyNum[i]);
        printf("Enter player %d's rating:\n", i + 1);//i + 1 is needed to prompt correct order
        scanf("%d", &playerRating[i]);
        printf("\n");//newline for formating purposes
    }
    while (userOption != 'q'){//this loop will allow user to modify whatever till they quit
        printf("MENU\n");
        printf("p - Print roster\n");
        printf("u - Update player rating\n");
        printf("a - Print players above a rating\n");
        printf("r - Replace player\n");
        printf("q - Quit\n");
        printf("Choose an option:\n");
        scanf(" %c", &userOption);//scans for user input for menu options

        if (userOption == 'p'){//statement is for printing the roster
            printf("PLAYER ROSTER\n");//header for roster
            printf("----------------------------\n");//header for roster
            printf("|  Player|  Jersey|  Rating|\n");//header for roster
            for (int i = 0; i < numPlayers; ++i){//this loop prints the body of the roster
                printf("|%8d|%8d|%8d|\n", i + 1, jerseyNum[i], playerRating[i]);
            }
        
            printf("----------------------------\n");
        }
        else if (userOption == 'u'){//this statement is for updating a player's rating
            int newjersey;
            int arrayCheck = 0;//variable used to see if player is in the roster first
            printf("Enter a jersey number:\n");
            scanf(" %d", &newjersey);
            for(int i = 0; i < numPlayers; ++i){//loop is to search the array 
                if(jerseyNum[i] == newjersey){
                    arrayCheck = 1;//if player is in roster, it will update 
                }
            }
            if (arrayCheck == 1){//if player was found then it will allow to modify
                for(int i = 0; i < numPlayers; ++i){//this loop will allow user to modify if player was found
                    if(jerseyNum[i] == newjersey){//goes through the array again till it finds the player
                        printf("Enter a new rating for player:\n");
                        scanf(" %d", &playerRating[i]); 
                    }
                }
            }
            else{//this will print if player not found
                printf("Player not in roster.\n");
            }
        }
        else if (userOption == 'a'){//this statement is for printing all players above a certain rating
            int ratingsearch;
            printf("Enter a rating:\n");
            scanf(" %d", &ratingsearch);//user enters desired rating 
            printf("PLAYER RATING ABOVE %d\n", ratingsearch);//header for roster
            printf("----------------------------\n");//header for roster
            printf("|  Player|  Jersey|  Rating|\n");//header for roster
            for (int i = 0; i < numPlayers; ++i){
                if (ratingsearch < playerRating[i]){//this loop prints the body of the roster
                    printf("|%8d|%8d|%8d|\n", i + 1, jerseyNum[i], playerRating[i]);
                }
            }
            printf("----------------------------\n");
        }
        else if (userOption == 'r'){//this statement is for replacing a jersey and rating number
            int jerseyToReplace;
            int replacementJersey;
            int newRating;
            int arrayCheck = 0;//variable used to see if player is in the roster first
            printf("Enter a jersey number:\n");
            scanf(" %d", &jerseyToReplace); 
            for(int i = 0; i < numPlayers; ++i){//loop is to search the array 
                if (jerseyNum[i] == jerseyToReplace){
                    arrayCheck = 1;//if player is in roster, it will update 
                }
            }
            if (arrayCheck == 1){//if player was found then it will allow to modify
                for(int i = 0; i < numPlayers; ++i){//this loop will allow user to modify if player was found
                    if (jerseyNum[i] == jerseyToReplace){//goes through the array again till it finds the player
                        printf("Enter a new jersey number:\n");
                        scanf(" %d", &replacementJersey);//number to replace jersey with
                        printf("Enter a rating for the new player:\n");
                        scanf(" %d", &newRating);//new rating for new jersey
                        jerseyNum[i] = replacementJersey;
                        playerRating[i] = newRating;
                    }
                }
            }
            else{//this will print if player not found
                printf("Player not in roster.\n");
            }
        }
    }
    return 0;
}