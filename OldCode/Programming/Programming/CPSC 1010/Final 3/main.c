#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*Number of words read = 65
Number of vowels = 106
Number of periods = 2
Number of question marks = 2
Shortest word = a
Shortest word count = 1
Longest word = Congratulations!
Longest word count = 16
Average word length = 4.5*/

int main(void){
    char inputFileName[100];
    char fileName[100];
    int numRead;
    char* subString = NULL;
    FILE* inFile = NULL;

    //get the file name for user input
    scanf("%s", inputFileName);

    //pointed the file pointer at an open file
    inFile = fopen(inputFileName, "r");

    //error check that fopen actually worked
    if (inFile == NULL){
        printf("No data found: file %s is empty.\n", inputFileName);
        return -1;
    }
     numRead = fscanf(inFile, "%s", fileName);
    int j = 0;//need a variable to count the words
    strcpy(inFile, subString);
    while(!feof(inFile)){
        if (numRead == 1){

            

            for(int i = 0; i < strlen(subString); ++i){
            //if there is a space and if there is not a space next, count up
            if(isalpha(subString[i]) && subString[i + 1] == ' '){
                ++j;
            }
            if(isalpha(subString[i]) && ispunct(subString[i + 1]) && subString[i + 1] != 39){
                ++j;
            }
            }
            if(isalpha(subString[strlen(subString) - 1])){
                ++j;
            }
           
            //go get the next string
           numRead = fscanf(inFile, "%s", fileName);
        }
        
    }
    printf("Number of words read = %d", j);

    //close the open file before exiting program
    fclose(inFile);
    return 0;
}