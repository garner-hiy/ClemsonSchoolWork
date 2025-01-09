//scanf, fgets and strcmp

#include <stdio.h>
#include <string.h>

int main (void){

    char original[50];
    char reversed[50];

    fgets(original, 50, stdin);
    
    if(original[strlen(original) - 1 ] == '\n'){//This is for fgets
        original[strlen(original) - 1] = '\0';
    }

    //this is a better way to reverse the string
    int j = 0;
    for (int i = strlen(original) - 1; i >= 0; --i){
        reversed[j] = original[i];
        ++j;
    }

    printf("string 1 = %s\n", original);
    printf("string 2 = %s\n", reversed);

    /*if (strcmp(original, reversed) == 0) {
        printf("Strings are the same!\n");
    }
    else{
        printf("String are NOT the same!\n");
    }*/

    return 0;
}