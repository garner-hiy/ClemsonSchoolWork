#include <stdio.h>
#include <string.h>

int main(void) {
    char string[50], temp;//user input
    char d[2] = "d";//used for strcmp
    char done[5] = "done";//used for strcmp
    char Done[5] = "Done";//used for strcmp

    printf("Please enter a line of text (maximum 50 characters).");
    printf(" Type done, Done, or d to exit program.\n");
    scanf(" %[^\n]s", string);
    /* This first prompt is to get the first input and
    after the if and else statement the user will enter a loop that will 
    update to the new prompt. 
    
    Originally the function strrev was to be used, but this function is not
    in the zybooks string.h library. Thus there is way more coding needed.
    */

    if (strcmp(string, d) == 0 || strcmp(string, done) == 0 || strcmp(string, Done) == 0){
        return -1; //this if statement is to determine if the user wants to quit
    }
    else{// this is the place where strrev would have been used
        int i, left, right, len;
        len = strlen(string);//need the string length 
        left = 0;// for setting left index with 0
        right = len - 1; //set right index with len - 1
        for(i = left; i < right; i++){// this loop is needed to store reverse string
            temp = string[i]; //need to assgin temp string with the user string
            string[i] = string[right];
            string[right] = temp;
            right--;
        }
        printf("%s\n", string);
    }
    int i = 0; //needed for condition in the loop
    while (i == 0){//this loop is designed to loop forever
        printf("Please enter another line of text (maximum 50 characters). ");
        printf("Type done, Done, or d to exit program.\n");
        scanf(" %[^\n]s", string);

        if (strcmp(string, d) == 0 || strcmp(string, done) == 0 || strcmp(string, Done) == 0){
            return -1; // this statement will break out of the loop
        }
        else{// this else will print string in reverse and allow for looping again
            int i, left, right, len;
            len = strlen(string);
            left = 0;
            right = len - 1;
            for(i = left; i <right; i++){
                temp = string[i];
                string[i] = string[right];
                string[right] = temp;
                right--;
            }
            printf("%s\n", string);
        } 
    }

    return 0;
}