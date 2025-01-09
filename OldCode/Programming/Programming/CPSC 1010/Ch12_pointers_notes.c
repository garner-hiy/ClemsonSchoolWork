/* Ch 12 Pointers

int main (void){

    int x = 0;
    int y = 0;

    int* ptrX = NULL;
    //int *ptrX; same thing just different ways to write it
    int* ptrY = NULL;
    //pointers only hold the memory address of the variable

    printf("---------------------------------\n");
    printf("Intial data value of x = %d\n", x);
    printf("Intial data value of y = %d\n", y); 
    printf("Intial data value of ptrX = %p\n", (void*)ptrX);
    printf("Intial data value of ptrY = %p\n", (void*)ptrY);
    printf("---------------------------------\n");
    printf("Memory address of x is = %p\n", (void*)&x);
    printf("Memory address of y is = %p\n", (void*)&y);
    printf("Memory address of ptrX is = %p\n", (void*)&ptrX);
    printf("Memory address of ptrY is = %p\n", (void*)&ptrY);

    ptrX = &x;
    ptrY = &y;

    *ptrX = 10;
    *ptrY = 10;

    printf("---------------------------------\n");
    printf("New data value of x = %d\n", x);
    printf("New data value of y = %d\n", y); 
    printf("New data value of ptrX = %p\n", (void*)ptrX);
    printf("New data value of ptrY = %p\n", (void*)ptrY);
    printf("---------------------------------\n");
    printf("Memory address of x is = %p\n", (void*)&x);
    printf("Memory address of y is = %p\n", (void*)&y);
    printf("Memory address of ptrX is = %p\n", (void*)&ptrX);
    printf("Memory address of ptrY is = %p\n", (void*)&ptrY);

    return 0;
}
*/

/*String with pointers*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void){

    char firstName[50];//statically allocated array
    char* name = NULL;

    strcpy(firstName, "AJ");
    printf("------------------------------------\n");
    printf("Initial data value of firstName - %s\n", firstName);
    printf("Initial data value of name (as a pointer) = %p\n", (void*)name);
    printf("Initial data value of name (as a string) = %s\n", name);
    printf("Memory address of firstName = %p\n", (void*)&firstName);
    printf("Memory address of name = %p\n", (void*)&name);

    //name = firstName;   //does work because it makes two pointers that point to the same address
    //strcpy(name, firstName);   //does not work
    name = (char*)(malloc((strlen(firstName) + 1) * sizeof(char))); //need to account for the null, so add 1
    strcpy(name, firstName);

    printf("------------------------------------\n");
    printf("New data value of firstName - %s\n", firstName);
    printf("New data value of name (as a pointer) = %p\n", (void*)name);
    printf("New data value of name (as a string) = %s\n", name);
    printf("Memory address of firstName = %p\n", (void*)&firstName);
    printf("Memory address of name = %p\n", (void*)&name);


    return 0;
}

