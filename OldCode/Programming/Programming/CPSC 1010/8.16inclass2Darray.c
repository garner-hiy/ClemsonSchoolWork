#include <stdio.h>

int main(void) {

    int rows;
    int columns;

    printf("How many rows: \n");
    scanf("%d", &rows);
    printf("How many columns: \n");
    scanf("%d", &columns);

    int array[rows][columns];

    for (int r = 0; r < rows; ++r){
        for (int c = 0; c < columns; ++c){
            scanf("%d", &array[r][c]);//normally i and j
        }
    }

    for (int r = rows - 1; r >= 0; --r){
        for(int c = columns - 1; c >= 0; --c){
            printf("%d ", array[r][c]);
        }
        printf("\n");
    }

   return 0;
}