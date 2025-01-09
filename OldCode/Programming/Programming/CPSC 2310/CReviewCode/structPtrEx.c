#include <stdio.h>
#include <stdlib.h>
struct person {
   int age;         //4 bytes
   float weight;    //4 bytes
   char name[30];   //30 bytes 
};/*sizeof person is 40 bytes (the struct data size must be in multiples of 4)
   *int is 4 bytes; float is 4 bytes, char name is 30 bytes 38 is not a 
   *multiple of 4 so 2 bytes will be added to make the total size of the struct
   *40 bytes.*/

int main()
{
   //use the next 2 lines to determine the size of an instance of struct person
   //struct person test; 
   //printf("%lu\n", sizeof(test));
   struct person *ptr;
   int i, n;

   printf("Enter the number of persons: ");
   scanf("%d", &n);
   /*Since we will not know the number of person's we will need, we need
    *to dynamically allocate the memory for n numbers of struct person.
    *This will give us an array of person's */
   ptr = (struct person*) malloc(n * sizeof(struct person));

   for(i = 0; i < n; ++i)
   {
       printf("Enter first name and age respectively: ");
       /*
           (ptr+i)->name is the same as 
           ptr[i].name is the same as 
           (*(ptr+i)).name
        */
       //scanf("%s %d", ptr[i].name, &ptr[i].age);
       //scanf("%s %d", (ptr+i)->name, &(ptr+i)->age);
       //scanf("%s %d", (*(ptr+i)).name, &(ptr+i)->age);
       scanf("%s %d", ptr[i].name, &(*(ptr+i)).age);
   }

   printf("Displaying Information:\n");
   for(i = 0; i < n; ++i)
       printf("Name: %s\tAge: %d\n", ptr[i].name, (*(ptr+i)).age);

   return 0;
}