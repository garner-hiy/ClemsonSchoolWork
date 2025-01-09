#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
 
    FILE* in = fopen("input.txt", "r");
    
    //add code to check file opened successfully 
    /*if(in == NULL)
    {
        fprintf(stderr, "The file did not open!! Exiting program!!\n");
        exit(-1);
    }*/
    /*Can do the same with assert. You are basically asserting that something is
     *true.  If it is not assert will fail, print a message that it failed
     *exit the program. */
    assert(in != NULL);
    int num;

    /*For those that have not seen scanf and fscanf - these are used to read 
     *user data provided either from a file or the terminal (command line) */
    /*read one number from the file opened above. printf prints to stdout 
     *(terminal)*/
    /*in is the file pointer
     *"%d" is the format specifier. This describes the type of data being read
     *&num is where the data being read will be stored.  This must be a pointer. 
     *since num is not a pointer we use & to indicate address.*/
    fscanf(in, "%d", &num);
    printf("%d\n", num);

    printf("now the program will pause while it waiting for the user to type\n");
    scanf("%d", &num);
    printf("The user entered %d. scanf reads the number from stdin.\n", num);

    return 0;
}