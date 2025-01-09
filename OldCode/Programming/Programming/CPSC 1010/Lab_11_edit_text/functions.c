#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

void PrintMenu(){//function that prints out options 
    printf("MENU\n");
    printf("c - Number of non-whitespace characters\n");
    printf("w - Number of words\n");
    printf("f - Fix capitalization\n");
    printf("r - Replace all !'s\n");
    printf("s - Shorten spaces\n");
    printf("q - Quit\n\n");
}
//This function will execute the menu options and pass the string
void ExecuteMenu(char userChar, char* ptrstring){
    switch(userChar){
        case 'c':
            printf("Number of non-whitespace characters: %d\n\n", GetChars(ptrstring));
            break;
        case 'w':
            printf("Number of words: %d\n\n", GetWords(ptrstring));
            break;
        case 'f':
            FixCapitals(ptrstring);
            printf("Edited text: %s\n\n", ptrstring);
            break;
        case 'r':
            ReplaceExclamation(ptrstring);
            printf("Edited text: %s\n\n", ptrstring);
            break;
        case 's':
            ShortenSpaces(ptrstring);
            printf("Edited text: %s\n\n", ptrstring);
            break;        
    }
}
//this counts the charaters 
int GetChars(char* ptrstring){
    int count = 0;//need a variable to count the charaters

    for(int i = 0; i < strlen(ptrstring); ++i){
        if(ptrstring[i] != ' '){
            ++count;
        }
    }
    return count;//returns the amount of charaters
}
//this will count the words
int GetWords(char* ptrstring){
    int j = 0;//need a variable to count the words

    for(int i = 0; i < strlen(ptrstring); ++i){
        //if there is a space and if there is not a space next, count up
        if(isalpha(ptrstring[i]) && ptrstring[i + 1] == ' '){
            ++j;
        }
        if(isalpha(ptrstring[i]) && ispunct(ptrstring[i + 1]) && ptrstring[i + 1] != 39){
            ++j;
        }
    }
    if(isalpha(ptrstring[strlen(ptrstring) - 1])){
        ++j;
    }
    return j; //return the amount 
}
//used to fix the capitals at the beginning of sentences 
void FixCapitals(char* ptrstring){
    //need to do the first charater
    ptrstring[0] = toupper(ptrstring[0]);
    for(int i = 1; i < strlen(ptrstring); ++i){
        int j = 0;
        //if there is a letter and there is a space before it
        if(ptrstring[i] == '.' || ptrstring[i] == '!' || ptrstring[i] == '?'){
            while(!isalpha(ptrstring[i + j])){
                j++;
            }
            ptrstring[i + j] = toupper(ptrstring[i + j]);
        }
    }
}
//replaces the exclamation marks with a period
void ReplaceExclamation(char* ptrstring){
    for(int i = 0; i < strlen(ptrstring); ++i){
        //if there is an exclamation, then replace with period
        if(ptrstring[i] == '!'){
            ptrstring[i] = '.';
        }
    }
}
//shortens the extra spaces
void ShortenSpaces(char* ptrstring){
    char temp[250];//need a temp string
    int j = 0;
    for(int i = 0; i < strlen(ptrstring); ++i){
        //if there is a space and another space, then execute
        if(ptrstring[i] == ' ' && ptrstring[i + 1] == ' '){
            continue;
        }
        //if the first element is a space, then execute
        if((i == 0) && (isspace(ptrstring[i]))){
            continue;
        }
        else{
            temp[j] = ptrstring[i];
            j++;
        }
    }
    temp[j] = '\0';//adds the null
    strcpy(ptrstring, temp);//copies the modified string the the original
}