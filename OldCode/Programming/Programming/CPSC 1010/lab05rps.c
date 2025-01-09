//AJ Garner
//Lab Section 1
//Lindsey Kirtley, Ashley Moody, Davis Little
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void){
    char p1name[40];//player 1 name
    char p2name[40];//player 2 name
    int rounds;     //number of rounds to play
    int randNum;    //random number used to seed
    int rps1;       //used to store first player seed
    int rps2;       //used to store second player seed
    int numWins1 = 0;//stores player 1 wins
    int numWins2 = 0;//stores player 2 wins
////////////////////////////////////////////////////////
//dashes break up code for easier reading
    printf("Enter player 1: \n");
    scanf(" %s", p1name);
    printf("Enter player 2: \n");
    scanf(" %s", p2name);
    printf("How many rounds to play?\n");
    scanf(" %d", &rounds);
////////////////////////////////////////////////////////
    while (rounds < 1){//checks that the number for rounds is valid
        printf("Must play at least 1 round! Please try again.\n");
        scanf(" %d", &rounds);
    }
////////////////////////////////////////////////////////
    printf("Pick a number to randomize game: \n\n"); 
    scanf(" %d", &randNum);
    srand(randNum);
////////////////////////////////////////////////////////

    
    printf("Starting game with %s versus %s for %d rounds!\n", p1name, p2name, rounds);
    for (int i = 0; i < rounds; ++i){ //loops through the games
        rps1 = rand() % 3;
        rps2 = rand() % 3;
//////////////     rock = 0 Paper = 1 Scissors = 2
        if (rps1 == rps2){
            printf("Round %d is a TIE\n", i + 1);
        }
        else if (rps1 == 0 && rps2 == 2){
            printf("%s wins Round %d with ROCK\n", p1name, i + 1);
            ++numWins1;
        }
        else if (rps1 == 0 && rps2 == 1){
            printf("%s wins Round %d with PAPER\n", p2name, i + 1);
            ++numWins2;
        }
        else if (rps1 == 1 && rps2 == 0){
            printf("%s wins Round %d with PAPER\n", p1name, i + 1);
            ++numWins1;
        }
        else if (rps1 == 1 && rps2 == 2){
            printf("%s wins Round %d with SCISSORS\n", p2name, i + 1);
            ++numWins2;
        }
        else if (rps1 == 2 && rps2 == 0){
            printf("%s wins Round %d with ROCK\n", p2name, i + 1);
            ++numWins2;
        }
        else if (rps1 == 2 && rps2 == 1){
            printf("%s wins Round %d with SCISSORS\n", p1name, i + 1);
            ++numWins1;
        }
    }
////////////////////////////////////////////////////////
    printf("\n");
    printf("%s wins %d and %s wins %d.\n", p1name, numWins1, p2name, numWins2);
////////////////////////////////////////////////////////

    if (numWins1 > numWins2){// checks who won
        printf("GAME WINNER - %s!\n", p1name);
    }
    else {
        printf("GAME WINNER - %s!\n", p2name);
    }
    if (numWins1 == numWins2){// checks if a tie
        printf("TIE\n");
    }

    

   return 0; 
}