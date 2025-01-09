#include <stdio.h>
//https://www.educba.com/fseek-in-c/

int main()
{
    FILE *fx = fopen("new_file.txt", "r");
    //Using the fseek function to move the file pointer to the end
    fseek(fx, 0, SEEK_END);//change to -1 or something else
    // Using the file function in order to Print the position of file pointer
    printf("Position of file pointer is : ");
    printf("%ld \n", ftell(fx));
    // Using the file function 'fseek' to move the file position 10 characters 
    //ahead from the beginning of the file
    fseek(fx,10,SEEK_SET);
    int ch;
    // printing the resulting file after 10 characters
    printf("Resulting bytes after the 10 characters in a file are: ");
    while( (ch=fgetc(fx)) != EOF)
    // using function 'putchar(ch)'' to print the file characters to stdout
    putchar(ch);
    return 0;
}