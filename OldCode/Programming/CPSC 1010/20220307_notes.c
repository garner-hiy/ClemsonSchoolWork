//Read in a 2D array of strings

#include <stdio.h>
#include <string.h>

int main (void){
    int numWords;
    
    printf("How many words to enter: \n");
    scanf("%d", &numWords);

    char list1[numWords][20];

    for(int i = 0; i < 10; ++i){//no need for inner loop because string.h allows for jsut one loop
        scanf("%s", list1[i]);
    }

        

    return 0;
}