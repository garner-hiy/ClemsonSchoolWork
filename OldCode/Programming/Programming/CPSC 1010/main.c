/*AJ Garner
Lab Section 1
Lindsey Kirtley, Ashley Moody, Davis Little*/

#include <stdio.h>
#include <string.h>

typedef struct PlayerInfoStruct_struct{//this struct sets all the information
    char firstname[20];//first name
    char lastname[20];//last name
    int jerseynum;// jersey number
    int rating;// player rating
}PlayerInfo;//type 
//below are all the prototypes
void GetPlayerInfo(PlayerInfo player[], int size);
void PrintRoster(PlayerInfo player[], int size);
void UpdateRating(PlayerInfo player[], int size);
void FindAbove(PlayerInfo player[], int size);
void ReplacePlayer(PlayerInfo player[], int size);

int main (void){
    char userOption = 'b';//variable used to interact with menu
    int numPlayers;//number of players to input

    printf("How many players to enter: \n");
    scanf("%d", &numPlayers);
    PlayerInfo player[numPlayers];
    GetPlayerInfo(player, numPlayers);

    while (userOption != 'q'){//this loop will allow user to modify whatever till they quit
        printf("MENU\n");
        printf("p - Print roster\n");
        printf("u - Update player rating\n");
        printf("a - Print players above a rating\n");
        printf("r - Replace player\n");
        printf("q - Quit\n");
        printf("Choose an option:\n");
        scanf(" %c", &userOption);//scans for user input for menu options
        switch(userOption){
            case 'p'://this prints out the roster
                PrintRoster(player, numPlayers);
            break;
            case 'u'://this statement is for updating a player's rating 
                UpdateRating(player, numPlayers);              
            break;
            case 'a'://this statement is for printing all players above a certain rating 
                FindAbove(player, numPlayers);          
            break;
            case 'r'://this statement is for replacing a jersey and rating number 
                ReplacePlayer(player, numPlayers);         
            break;
        }
    }
    return 0;
}

void GetPlayerInfo(PlayerInfo player[], int size){
    for (int i = 0; i < size; ++i){//this loop allows user to fill the arrays
        printf("Enter player %d's first name:\n", i + 1);
        scanf("%s", player[i].firstname);
        printf("Enter player %d's last name:\n", i + 1);
        scanf("%s", player[i].lastname);
        printf("Enter player %d's jersey number:\n", i + 1);
        scanf("%d", &player[i].jerseynum);
        printf("Enter player %d's rating:\n", i + 1);
        scanf("%d", &player[i].rating);
    }
}
void PrintRoster(PlayerInfo player[], int size){
    char fullname[20];//needed to print proper formating
    printf("PLAYER ROSTER\n");//header for roster
    printf("-------------------------------------------------\n");//header for roster
    printf("|  Player|                Name|  Jersey|  Rating|\n");//header for roster
    for (int i = 0; i < size; ++i){//this loop prints the body of the roster
        strcpy(fullname, player[i].firstname);
        strcat(fullname, " ");//adds the space needed between the name
        strcat(fullname, player[i].lastname);
        printf("|%8d|%20s|%8d|%8d|\n", i + 1, fullname, player[i].jerseynum, player[i].rating);
    }
    printf("-------------------------------------------------\n");
}
void UpdateRating(PlayerInfo player[], int size){
    int newjersey;
    int arrayCheck = 0;//variable used to see if player is in the roster first
    printf("Enter a jersey number:\n");
    scanf(" %d", &newjersey);
    for(int i = 0; i < size; ++i){//loop is to search the array 
        if(player[i].jerseynum == newjersey){
            arrayCheck = 1;//if player is in roster, it will update 
        }
    }
    if (arrayCheck == 1){//if player was found then it will allow to modify
        for(int i = 0; i < size; ++i){//this loop will allow user to modify if player was found
            if(player[i].jerseynum == newjersey){//goes through the array again till it finds the player
                printf("Enter a new rating for player:\n");
                scanf(" %d", &player[i].rating); 
            }
        }
    }
    else{//this will print if player not found
        printf("Player not in roster.\n");
    }
}
void FindAbove(PlayerInfo player[], int size){
    int ratingsearch;
    char fullname[20];//needed for proper formating
    printf("Enter a rating:\n");
    scanf(" %d", &ratingsearch);//user enters desired rating 
    printf("PLAYER RATING ABOVE %d\n", ratingsearch);//header for roster
    printf("-------------------------------------------------\n");//header for roster
    printf("|  Player|                Name|  Jersey|  Rating|\n");//header for roster
    for (int i = 0; i < size; ++i){
        if (ratingsearch < player[i].rating){//this loop prints the body of the roster
            strcpy(fullname, player[i].firstname);
            strcat(fullname, " ");
            strcat(fullname, player[i].lastname);
            printf("|%8d|%20s|%8d|%8d|\n", i + 1, fullname, player[i].jerseynum, player[i].rating);
        }
    }
    printf("-------------------------------------------------\n");
}
void ReplacePlayer(PlayerInfo player[], int size){
    int jerseyToReplace;
    int arrayCheck = 0;//variable used to see if player is in the roster first
    printf("Enter a jersey number:\n");
    scanf(" %d", &jerseyToReplace); 
    for(int i = 0; i < size; ++i){//loop is to search the array 
    if (player[i].jerseynum == jerseyToReplace){
            arrayCheck = 1;//if player is in roster, it will update 
        }
    }
    if (arrayCheck == 1){//if player was found then it will allow to modify
        for(int i = 0; i < size; ++i){//this loop will allow user to modify if player was found
            if (player[i].jerseynum == jerseyToReplace){//goes through the array again till it finds the player
                printf("Enter a first name for the new player: \n");
                scanf("%s", player[i].firstname);
                printf("Enter a last name for the new player: \n");
                scanf("%s", player[i].lastname);
                printf("Enter a jersey number for the new player:\n");
                scanf(" %d", &player[i].jerseynum);//number to replace jersey with
                printf("Enter a rating for the new player:\n");
                scanf(" %d", &player[i].rating);//new rating for new jersey
            }
        }
    }
    else{//this will print if player not found
        printf("Player not in roster.\n");
    }
}