//quick format starter

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void){

    return 0;
}

strchr(sourceStr, searchChar);  //returns pointer to first occurrence
strrchr(sourceStr, searchChar); //returns pointer to LAST occurrence 
           //(searches in reverse, hence middle 'r' in name)

strstr(str1, str2);  //returns a char pointer pointing to 
           //first occurrence of string str2 within string str1



//fgets
fgets(original, 50, stdin);
    
    if(original[strlen(original) - 1 ] == '\n'){//This is for fgets
        original[strlen(original) - 1] = '\0';
    }

//malloc uses for int
pointerVariableName = (type*)malloc(sizeof(type));
//for arrays
pointerVariableName = (dataType*)malloc(numElements * sizeof(dataType));
//free
free(pointerVariable);
//realloc
pointerVariable = (type*)realloc(pointerVariable, numElements * sizeof(type));



//Struct
typedef struct Name_struct{
    //variables
}Name;

//pointer with structs    aka: member access operator
structPtr->memberName;     // Equivalent to (*structPtr).memberName


//string reverse
void stringReverse(char* original, int size){
    char reversed[size];
    int j = 0;
    for (int i = strlen(original) - 1; i >= 0; --i){
        reversed[j] = original[i];
        ++j;
    }
    strcpy(reversed, original);
}
