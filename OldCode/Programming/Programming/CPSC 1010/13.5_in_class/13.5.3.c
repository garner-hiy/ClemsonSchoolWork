#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    //char inputFileName[100];
    char fileName[100];
    int numRead = 0;
    char* subString = NULL;

    //create input and output file pointer and initialize to NULL
    FILE* inFile = NULL;
    FILE* outFile = NULL;

    if(argc != 3){
        printf("Usage: myprog.exe inputFileName outputFileName\n");
        return 1;
    }

    //get the file name from the command line

    //print for demo
    printf("argc = %d\n", argc);
    printf("argv[0] = %s\n", argv[0]);
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);

    //pointed the file pointer at an open file
    inFile = fopen(argv[1], "r");
    outFile = fopen(argv[2], "w");

    //error check that fopen actually worked
    if (inFile == NULL){
        printf("Could not open file %s.\n", argv[1]);
        return -1;
    }
    if (outFile == NULL){
        printf("Could not open file %s.\n", argv[2]);
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