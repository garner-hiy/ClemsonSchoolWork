//used to count number of letters in a string 

#include <stdio.h>
#include <string.h>

int main (void)
{
    char userChar;
    char userString[50];
    int count = 0;      //needed to count the letters

    printf("Enter a character: \n");
    scanf("%c", &userChar);
     //gotta scan for inputs
    printf("Enter a string: \n");
    scanf("%s", userString);
    
    for (int i = 0; userString[i]; i++) { // Loop is used to update int count
       if (userString[i] == userChar) {   // if statement is needed to determine if char is there
          count++;
       }
    }
    
    if (count == 1) { // only need this if for if the count is just 1
     printf("%d %c\n", count, userChar);  
    }
    else {           // everything else will be multiples of the char
       printf("%d %c's\n", count, userChar);
    }
    
    return 0;
}