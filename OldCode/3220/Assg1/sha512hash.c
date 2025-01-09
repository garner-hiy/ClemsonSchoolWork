/*
Name: AJ Garner
Class: CPSC 3220

Purpose: The program will take in a "word" from the CL,
calculate the SHA512 hash value of it and print it.

How to Compile and run Everything:
gcc sha512hash.c -o sha512hash -lcrypt
gcc asg1.c -o asg1 -pthread
./asg1 <word> <mm/dd/yyyy>
*/

#include <stdio.h>
#include <string.h>
#include <crypt.h>

int main(int argc, char* argv[]){

    //this is the SHA512 hash variable
    char *hash = crypt(argv[1],"$6$HiMom");

    printf("SHA512 of %s is %s\n", argv[1], hash);

    return 0;
}