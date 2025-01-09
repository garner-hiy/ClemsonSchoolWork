#include <stdio.h>

int DaysInFeb (int userYear);//prototype

int main (void){

    int userYear;//user inputted variable
    printf("Please enter a year: \n");
    scanf("%d", &userYear);

    /*When there is a call to the function,
    the return will be either 28 or 29 days.*/ 
    
    printf("There were %d days in February in the year %d.\n", DaysInFeb(userYear), userYear);

    return 0;
}

int DaysInFeb (int userYear){
    
    if (userYear % 4 == 0 && userYear % 100 != 0) {
        return 29;//if this statment is true it will return the number 29
    }
    else if (userYear % 400 == 0) {
        return 29;//if this statment is true it will return the number 29
    }
    else {
        return 28;//everything else will return 28
    }
}