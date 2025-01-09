#include <stdio.h>

int GetMax(int list[], int listSize);//prototype

int main (void){

    int listSize;//needed to set the amount of integers in the array

    printf("How many values to enter?\n");
    scanf("%d", &listSize);//grabbing array size from user

    int list[listSize];//array delared after size 
    int tempList[listSize];//need temp array for copying integers
    
    printf("Please enter %d values: \n", listSize);

    for (int i = 0; i < listSize; ++i){//loop is for array
        scanf("%d", &list[i]);
    }

    int max = GetMax(list, listSize);//call to the function
     
    for (int i = 0; i < listSize; ++i){
        tempList[i] = list[i];//copies integers to tempList from list
        list[i] = max;//changes all integer in orignal array to max
        list[i] -= tempList[i];//subtracts original integers in tempList from max integers in list
    }

    printf("Adjusted list: ");
    for (int i = 0; i < listSize; ++i){//loop prints out array
        printf("%d ", list[i]);
    }
    printf("\n");//finish with newline

    return 0;
}

int GetMax(int list[], int listSize){//function
    int max = list[0];//max integer is delared first

    for (int i = 0; i < listSize; ++i){//loop finds if there is a higher integer
        if (list[i] > max){//if statement updates new max
            max = list[i];
        }
    }
    return max;
}