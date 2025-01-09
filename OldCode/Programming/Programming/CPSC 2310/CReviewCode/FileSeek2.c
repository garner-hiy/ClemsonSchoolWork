// C library mandatory to use C I/O operation
#include <stdio.h>
int main () {
// defining the file pointer in order to perform file operations
FILE *fx;
// Opening a file using the 'fopen()' function in write mode
fx = fopen("file_new.txt","w+");
// writing in the file using 'fputs() function'
fputs("Yes, we are learning fseek function in C", fx);
//using fseek() function to move the file pointer after 12 characters
fseek( fx, 12, SEEK_SET );
// inserting the data in the file
fputs("trying to insert something", fx);
//closing the file using 'fclose() function'
fclose(fx);
return(0);
}