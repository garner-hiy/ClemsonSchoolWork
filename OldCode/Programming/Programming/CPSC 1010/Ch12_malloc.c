//Pointers + malloc examples

#include <stdio.h>
#include <stdlib.h>


int main (void){
    int* array = NULL;
    int numVals;

    scanf("%d", &numVals);

    array = (int*)(malloc(numVals * sizeof(int)));

    if (array == NULL){
        printf("Dynamic allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < numVals; ++i){
        scanf("%d", &array[i]);
    }
    printf("Original values: ");
    for (int i = 0; i < numVals; ++i){
        printf("%d ", array[i]);
    }

    scanf("%d", &numVals);

    array = (int*)(realloc(array, numVals * sizeof(int)));

    for (int i = 0; i < numVals; ++i){
        printf("%d ", array[i]);
    }

    free(array);
    
    return 0;
}