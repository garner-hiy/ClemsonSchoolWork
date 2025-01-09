#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void) {
    char string[50];

    fgets(string, 50, stdin);

    for(int i = 0; i < strlen(string); ++i){
        if (isalpha(string[i])){
            printf("%c", string[i]);
        }
    }
    printf("\n");
    
    return 0;
}