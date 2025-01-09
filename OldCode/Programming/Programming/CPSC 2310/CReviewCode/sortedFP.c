#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*This code came from learn C the hard way website.  The actual link I got it 
 * from years ago no longer works, so I removed it from this document.  */


/*A typedef creates a alias type, in this case for a function pointer*/
//typedef int (*compare_cb)(int a, int b);
int (*compare_cb)(int a, int b);

/*Function Prototypes*/
int *bubble_sort(int *numbers, int count, int (*compare_cb)(int, int));
int sorted_order(int a, int b);
int reverse_order(int a, int b);
int strange_order(int a, int b);
void test_sorting(int *numbers, int count, int (*compare_cb) (int, int));

int main(int argc, char *argv[])
{
	/*This variable tells me how many numbers need to be sorted*/
	int count = argc -1;
	int i = 0;
	/*This is a pointer that points to the first number on the command line*/
	char **inputs = argv + 1;

	/*Since we do not know how many numbers are going to listed on the command
	 *line I need to dynamically allocate the memory for the numbers.*/
	int *numbers = malloc(count * sizeof(int));

	/*I am going to loop through the numbers entered on the command line
	 *storing them in the dynamically allocated memory.
	 *I have to use atoi because ?? what type is the variable inputs and 
	 *what type is the variable numbers*/
	for(i = 0; i < count; i++)
	{
		numbers[i] = atoi(inputs[i]);
	}

	/*I am passing the function name to the function.  Remember this function
	 *had a function pointer as its third parameter. That Funciton pointer 
	 *matches the prototype of these functions. 
	 *BTW, test_sorting will call bubble_sort which in turns will call 
	 *the algorithm used to determine the method of sorting*/
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);

	/*Now that I am done I need to give the memory back to the operating system 
	 *by calling free.*/

	free(numbers);
	numbers = 0;

	return 0;

}

/*A classic bubble sort function that uses the compare_cb to do the sorting*/
//int *bubble_sort(int *numbers, int count, compare_cb cmp)
int *bubble_sort(int *numbers, int count, int (*compare_cb)(int, int))
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));
	/*void * memcpy(void *to, const void *from, size_t numBytes);
	 *copies "numBytes" bytes from address "from" to address "to"
	 *We also have memset.
	 void *memset(void *ptr, int x, size_t n);
	 ptr ==> Starting address of memory to be filled
     x   ==> Value to be filled
     n   ==> Number of bytes to be filled starting 
             from ptr to be filled
	 **/
	memcpy(target, numbers, count * sizeof(int));

	for(i =0; i < count -1; i++)
	{
		for(j = 0; j < count - 1; j++)
		{
			//if(cmp(target[j], target[j+1]) > 0)
			if((*compare_cb)(target[j], target[j+1]) > 0)
			{
				temp = target[j+1];
				target[j+1] = target[j];
				target[j] = temp;
			}
		}
	}
	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b == 0)
	{
		return 0;
	}
	else
	{
		//printf("a mod b %d\n", a % b);
		return a % b;
	}


}

void test_sorting(int *numbers, int count, int (*compare_cb) (int, int))
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, (*compare_cb));

	for(i = 0; i < count; i++)
	{
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}