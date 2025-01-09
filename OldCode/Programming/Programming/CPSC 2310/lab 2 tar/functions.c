/*************************
*AJ Garner
*Kannniese Chen
*CPSC 2311 001
*adgarne@g.clemson.edu
*************************/
#include "functions.h"

void numSentences(FILE* in, FILE* out){
    //used to count the number of bytes
    long    numbytes;

    //this is the char array used to locate charaters
    char    *text;

    //this block of fseek will reed the file and give the amount of bytes
    fseek(in, 0L, SEEK_END);
    numbytes = ftell(in);
    fseek(in, 0L, SEEK_SET);  

    //need to alocate memory to store later
    text = (char*)calloc(numbytes, sizeof(char)); 

    //fread will read everything to the char array aka string
    fread(text, sizeof(char), numbytes, in);

    //count variable to keep count
    int count = 0;

    //this for loop will determine if the postion is the end of the sentence
    //it will also check for double of the charaters
    for(int i = 0; i < numbytes; i++){
        if(text[i] == '.' && text[i+1] != '.')
            count++;
        
        else if(text[i] == '!' && text[i+1] != '!')
            count++;
        
        else if(text[i] == '?' && text[i+1] != '?')
            count++;
        
        else
            continue;

    }

    //this fprintf will print the results to file
    fprintf(out, "Total number of sentences: %d\n", count);
}

void numWords(FILE* in, FILE* out){
    //used to count the number of bytes
    long    numbytes;

    //this is the char array used to locate whitespace
    char    *text;

    //this block of fseek will reed the file and give the amount of bytes
    fseek(in, 0L, SEEK_END);
    numbytes = ftell(in);
    fseek(in, 0L, SEEK_SET);  

    //need to alocate memory to store later
    text = (char*)calloc(numbytes, sizeof(char)); 

    //fread will read everything to the char array aka string
    fread(text, sizeof(char), numbytes, in);

    //count variable to keep count
    int count = 0;

    //this for loop will determine if the postion is the end of the sentence
    //it will also check for double of the charaters
    for(int i = 0; i < numbytes; i++){
        if(text[i] == ' ' && text[i+1] != ' ')
            count++;
        else if(text[i] == '\n' && text[i+1] != '\n')
            count++;
        else
            continue;
    }
    
    //this fprintf will print the results to file
    fprintf(out, "Total number of words: %d\n", count);
}
