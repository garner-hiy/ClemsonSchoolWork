#include <stdio.h>
#include <stdlib.h>
#define R  3
const int C = 4;
int main()
{
	int i, j, count;

  /*This creates an array of size R (3)  This is basically a double pointer*/
	int *arr[R];

  /*Remember a call to malloc returns a pointer to a block of memory.
   *Each array element (arr[i]) is pointing to a block of memory of size
   *C times the size of an int.  This will allow me to access the the data
   *using 2D array notation*/
	for (i=0; i < R; i++)
  {
		arr[i] = (int *)malloc(C * sizeof(int));
  }

	/*Note that arr[i][j] is same as *(*(arr+i)+j)*/
	count = 0;
	for (i = 0; i < R; i++)
  {
	   for (j = 0; j < C; j++)
     {
		    arr[i][j] = ++count; // Or *(*(arr+i)+j) = ++count
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
	printf("\n");

	/* Code for further processing and free the
	dynamically allocated memory */
	for (i=0; i<R; i++)
  {
		free(arr[i]);
  }


return 0;
}
