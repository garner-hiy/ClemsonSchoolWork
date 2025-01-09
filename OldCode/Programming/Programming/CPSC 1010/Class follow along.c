#include <stdio.h>
#include <string.h>

int main (void) {

    char searchChar;
    char string1[50];
    char string2[50];

    printf("Enter a word or phrase: ");
    scanf("%s", string1);

    printf("Enter another word or phrase: ");
    scanf("%s", string2);

    printf("Enter a search character: ");
    scanf(" %c", &searchChar);

    printf("%-11s : %s\n", "String 1", string1);
    printf("%-11s : %s\n", "String 2", string2);
    printf("%-11s : %c\n", "Search char", searchChar);

    //get string lengths
    printf("String 1 is %d chars long.\n", (int)strlen(string1));
    printf("String 2 is %d chars long.\n", (int)strlen(string2));
    //compare string 1 and string 2
    if (strcmp(string1, string2) == 0) {
        printf("The strings are equal.\n");
    }
    else {
        printf("The strings are not equal.\n");
    }

    //look for first and last letter of word
    printf("The first letter of string 1 is %c.\n", string1[0]);
    printf("The last letter of string 2 is %c.\n", string2[strlen(string2) - 1]);

    //look for character in string
   if (strchr(string1, searchChar) != NULL) {
       printf("Char %c found in %s.\n", searchChar, string1);
   }
   else {
       printf("Not found.\n");
   }

    return 0;
}