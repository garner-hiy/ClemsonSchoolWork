/**************************
 *AJ Garner                                *
 *CPSC2310 Spring 2023            *
 *UserName:  adgarne                              *
 *Instructor:  Dr. Yvon Feaster  *
*************************/
#include "functions.h"
int** readFile(FILE* fp, int *size)
{
    fscanf(fp, "%d", size);
    int num = *size;
    int index = 0;
    //printf("%d\n", num);
    int** mat = (int**)malloc(num * sizeof(int*));
    for(index = 0; index < num; index++)
        mat[index] = (int*)malloc(num * sizeof(int)); 

    int row = 0; 
    int col = 0;
    for(row = 0; row < num; row++)
    {
    
        for(col = 0; col < num; col++)
        {
            fscanf(fp, "%d", &(mat[row][col]));
        }
    }
    return mat;
}


void printMatrix (int** mat, int num)
{
    int row = 0; 
    int col = 0;
    for(row = 0; row < num; row++)
    {
        for(col = 0; col < num; col++)
        {
            printf("%.2d\t", mat[row][col]);
        }
        printf("\n");
    }
    
}

//This function will calculate the value of the matrix
int calculateVal(int** mat, int size){
    int row = 0; 
    int col = 0;
    //sum needed to calculate the value
    int sum = 0;

    //nested for loop to iterator through the matrix
    for(row = 0; row < size; row++){
        for(col = 0; col < size; col++){
            //calling functions to check conditions
            if(!isRightDiagonal(size, row, col) && 
            !isLeftDiagonal(row, col)){
                sum += mat[row][col];
            }
                       
        }
    }
    //printf needed for proper format
    printf("Total = %d\n", sum);
    return sum;
}
bool isRightDiagonal(int size, int row, int col){
    //if row + col is equal to the size
    return (row + col == size - 1)  ?  true : false;
}
bool isLeftDiagonal(int row, int col){
    //if row and col are equal 
    return (row == col) ? true : false;
}
