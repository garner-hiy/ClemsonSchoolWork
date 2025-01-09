#include<stdio.h>
#include<stdlib.h>
#define R 3
#define C 4

int main()
{
	int **arr;
	int count = 0,i,j;

	arr = (int **)malloc(sizeof(int *) * R);
	arr[0] = (int *)malloc(sizeof(int) * C * R);

	for(i = 1; i < R; i++)
		arr[i] = (*arr + (C * i));

	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count
		}
	}
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}

	free(arr[0]);
	free(arr);

	return 0;
}
