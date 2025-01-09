#include <stdio.h>
#include <stdlib.h>
 
//Maximum size of the array
#define MAX_SIZE  32
 
int main()
{
    //file pointer
    FILE *fp = NULL;
    char readFileData[MAX_SIZE] = {0};
 
    //open the file
    fp = fopen("test.txt", "r+");
    if(fp == NULL)
    {
        printf("Error in opening the file\n");
        exit(1);
    }
 
    // Read 5 out of the 9 characters from where fp is pointing and store it 
    // in readFileData
    fread(readFileData,sizeof(char),5, fp);
    //Display read data to stdout (standard out)
    //prototype for puts: int puts(const char *str);
    puts(readFileData);
    char readFileData2[MAX_SIZE] = {0};
    //Read the remaining characters
    /*What if I change 4 to 10000?  fread() reads up to length bytes from the 
     *file pointer referenced by stream . Reading stops as soon as one of 
     *the following conditions is met: length bytes have been read. 
     *EOF (end of file) is reached.*/
    fread(readFileData2,sizeof(char),4, fp);
    puts(readFileData2);
    puts("Now is the time for all good men come to the aid of their country.");

    //close the file
    fclose(fp);
 
    printf("Read file successfully\n");
 
    return 0;
}