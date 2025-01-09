 #include<stdio.h>
#include<stdlib.h>
const int rows = 3;
const int cols = 4;
int main()
{
	int count=1;

	int i = 0,j = 0;
    int header = rows * sizeof(int*);
    int data = rows * cols * sizeof(int);	
    int** rowptr = (int**)malloc(header + data);	
	int* buffer = (int*)(rowptr + rows);
	printf("Value of Buffer (the address where it points) %p\n", buffer);
	
	for(i = 0; i < rows; i++)
	{
		rowptr[i] = (buffer + (i * cols));
		printf("%p points to %p\n", &rowptr[i], rowptr[i]);
		//printf("%p\n", rowptr[i]);
			
	}
	//give them value
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			rowptr[i][j] = count++; 
		}
	}
	//print the values 
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%d ", rowptr[i][j]);
		}
		printf("\n");
	}

	
	free(rowptr);

	return 0;
}
