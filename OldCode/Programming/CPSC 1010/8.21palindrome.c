#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char string[50], blank[50],stemp[50], temp;
    //string = user input, blank = moddified user input
    //stemp = string to store blank before reversing the string
    //temp is for reversing loop
    int a = 0;//for counting charaters
    int b = 0;//for counting charaters into blank string
    
    printf("Please enter a word or phrase (maximum 50 characters): \n");
    scanf(" %[^\n]s", string);//read everything up to the Null

    while (string[a] != '\0'){//this while loop removes whitespace
        if (!(string[a] == ' ')) {
        blank[b] = string[a];
        b++;
      }
      a++;
    }
    
    for (int i = 0; blank[i]; ++i) {// this loop makes charaters lowercase
        blank[i] = tolower(blank[i]);
    }
    strcpy(stemp, blank);//copy blank to stemp before reversing blank
    
    //---Block of code used to reverse string-----------------//
    int i, left, right, len;
    len = strlen(blank);//need the string length 
    left = 0;// for setting left index with 0
    right = len - 1; //set right index with len - 1
    for(i = left; i < right; i++){// this loop is needed to store reverse string
        temp = blank[i]; //need to assgin temp string with the blank string
        blank[i] = blank[right];
        blank[right] = temp;
        right--;
    }
    //-------------------------------------------------------//

    /*This if and else statement is used to see if the modified 
    strings are equal. If they are not then it will print otherwise*/
    if (strcmp(stemp,blank) == 0){
        printf("'%s' is a palindrome.\n", string);//prints the original user string
    }
    else{
        printf("'%s' is not a palindrome.\n", string);
    }

    return 0;
}