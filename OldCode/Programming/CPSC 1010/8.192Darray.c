#include <stdio.h>
#include <string.h>

int main (void) {
    int numWords; // number of words to enter
    const int stringMaxLenght = 20; //sets max amount of charaters in strangs
    char *searchLetter;// needed to search for letter in strings
    char *foundWords;// needed to determine if strchr finds words

/////////////////////////////////////////////////////////////////////////////
///////////dashes used to break up code

    printf("How many words to enter: \n");
    scanf("%d", &numWords);

/////////////////////////////////////////////////////////////////////////////

    char stringArray[numWords][stringMaxLenght];// declare after number of words

/////////////////////////////////////////////////////////////////////////////

    printf("Please enter %d words: \n", numWords);
    for (int i = 0; i < numWords; ++i){
        scanf(" %s", stringArray[i]);
    }
/////////////////////////////////////////////////////////////////////////////
    
    printf("Enter a character to search: \n");
    scanf(" %c", &searchLetter);

/////////////////////////////////////////////////////////////////////////////

    printf("Character match found: ");
    for (int i = 0; i < numWords; ++i){// needed to loop through array
        foundWords = strchr(stringArray[i], searchLetter);// checks for the letter
        if (foundWords != NULL){// if it is not Null print the string
            printf("%s ", stringArray[i]);
        }  
    }

/////////////////////////////////////////////////////////////////////////////

    printf("\n");

    return 0;
}