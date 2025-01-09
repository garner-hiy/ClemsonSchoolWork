/**************************
 *AJ Garner                                *
 *CPSC2310 Spring 2023            *
 *UserName:  adgarne                              *
 *Instructor:  Dr. Yvon Feaster  *
*************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int** readFile(FILE* fp, int *size);
void printMatrix (int** mat, int num);

//added function prototypes
int calculateVal(int** mat, int size);
bool isRightDiagonal(int size, int row, int col);
bool isLeftDiagonal(int row, int col);