#include <stdio.h>
#include <string.h>

int main(void){
    char inputFileName[100];
    char fileName[100];
    int numRead = 0;
    char* subString = NULL;

    //create input and output file pointer and initialize to NULL
    FILE* inFile = NULL;
    FILE* outFile = NULL;

    //get the file name for user input
    scanf("%s", inputFileName);

    //pointed the file pointer at an open file
    inFile = fopen(inputFileName, "r");
    outFile = fopen("ParkPhoto_edited.txt", "w");

    //error check that fopen actually worked
    if (inFile == NULL){
        printf("Could not open file %s.\n", inputFileName);
        return -1;
    }
    if (outFile == NULL){
        printf("Could not open file %s.\n", inputFileName);
        return -1;
    }

    //assign the return of fscanf to a variable
    numRead = fscanf(inFile, "%s", fileName);

    //loop and read in one string at a time until the end of the file
    while(!feof(inFile)){
        //indicates that exactly 1 string was read from the file
        if (numRead == 1){

            //find the beginning of photo.jpg, point a new pointer there
           subString = strstr(fileName, "photo.jpg");

           //overwrite the substring with new text
           strcpy(subString, "info.txt");

            //print to screen
           printf("%s\n", fileName);

           //print to file
           fprintf(outFile, "%s\n", fileName);

            //go get the next string
           numRead = fscanf(inFile, "%s", fileName);
        }
        else{
            printf("Input failure before reaching end of file.\n");
            break;
        }
    }
    //close the open file before exiting program
    fclose(inFile);
    fclose(outFile);

    return 0;
}