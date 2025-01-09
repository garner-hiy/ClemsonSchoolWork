/*   This program illustrates dynamic memory allocation.   */

#include <stdio.h>
#include <stdlib.h>      // used for malloc and free


// another way to define a struct using typedef
typedef struct student
{
	int id;
	char mi;
} student_t;


int main()
{
	struct student aStudent;
	/*Because we used typedef with the student struct, we could have declared
	 *aStudent in the following way:  student_t aStudent;*/
	int numberOfStudents;

	// declare two pointers of type student_t
	student_t   *structPointer,   *memoryStart;
	int i;

	printf("Enter number of students: ");
	scanf("%d", &numberOfStudents);

	/*Dynamically allocate memory using malloc.
	 *Notice the type cast (student_t *)
	 *malloc returns a void *(pointer)  pointing at the start of the allocated
	 *memory*/
	memoryStart =  (student_t *) malloc(sizeof(aStudent) * numberOfStudents);

	/*test if malloc succeeds.
	 *malloc returns null if it failed to allocated the required memory*/
	if (memoryStart != NULL)
	{
		for (i = 0, structPointer = memoryStart; i < numberOfStudents;
			                                       i++, structPointer++)
		{
			/*notice how we access a struct field using a pointer. We are
			 *assigning id numbers to each student.  Also we do not need
			 *to increment structPointer after this assignment because it
			 *is being incremented in the for loop*/
    		structPointer->id = i;
    	}
	}
    // print out the ids of all the students
    for (i = 0, structPointer = memoryStart; i < numberOfStudents; i++)
    {
    	printf("%d\n", structPointer -> id);
      /*We did not increment the pointer in the for loop so it has to
      *be incremented here*/
      structPointer++;
    }

    /*Free the memory that has been allocated.
      We need to pass the address of the beginning of
      the allocated memory*/
      free(memoryStart);


	return 0;
}
