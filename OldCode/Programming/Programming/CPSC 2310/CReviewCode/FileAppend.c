#include <stdio.h>
#include <assert.h>

int main()
{
    FILE* fPtr = fopen("appendFile1.txt", "a");
    assert(fPtr != NULL);

    fprintf(fPtr, "I am adding info to this file.\n");
    
    /*rewind moves the pointer back to the beginning fo the file buffer. 
     *you can use fseek to move the pointer to various places in the file
     *buffer.*/
    rewind(fPtr);
    /* The file was opened using append mode.
     *Append always adds to the end of the file, even if I call rewind to the 
     *beginning of the file.*/
    fprintf(fPtr, "I am adding to the beginning of the file. (or not)\n");

    fclose(fPtr);
    return 0;

}
