#include <stdio.h>
#include <string.h>
#include <ctype.h>

void CreateAcronym(char userPhrase[], char userAcronym[]);//prototype

int main (void){
    char userPhrase[50];//the user's string
    char userAcronym[50];//the string the user's string will become
    printf("Enter a word or phrase (maximum 50 characters): \n");//prompt
    scanf("%[^\n]s", userPhrase);//scans everything till the enter
    CreateAcronym(userPhrase, userAcronym);//call to function
    printf("%s\n", userAcronym);

    return 0;
}

void CreateAcronym(char userPhrase[], char userAcronym[]){//function is void because it just needs to modify a string
    int j = 0;//variable used to put letters into the acronym string
    for(int i = 0; i < strlen(userPhrase); ++i){//loop is to check all the letters in the string
        if(isupper(userPhrase[i])){//if the charater is an uppercase, this if statement will execute
            userAcronym[j] = userPhrase[i];
            userAcronym[j + 1] = '.';//this will put a period after each uppercase
            ++j;//need to interate twice to keep the proper element in the acronym string
            ++j;
        }
    }
    userAcronym[j] = '\0';//need to add an null after the acronym string is done
}