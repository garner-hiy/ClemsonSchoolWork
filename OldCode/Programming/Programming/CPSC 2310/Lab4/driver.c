/**************************
 *AJ Garner                                *
 *CPSC2310 Spring 2023            *
 *UserName:  adgarne                              *
 *Instructor:  Dr. Yvon Feaster  *
*************************/
#include <stdio.h> 
#include <stdlib.h>
#include "functions.h"

int main(int argc, char** argv)
{
    //printf("cheking command line arguments\n");

    if (argc < 2) 
    { 
        printf("not enought argument: ./exe filename\n"); 
        exit(-1);
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp==NULL)
    {
        printf("fp did nto open\n"); 
        exit(-1);
    }
    int size = 0;
    int **mat = readFile(fp, &size);
    printMatrix(mat, size);

    //call to the function needed
    calculateVal(mat, size);

    return 0;
}