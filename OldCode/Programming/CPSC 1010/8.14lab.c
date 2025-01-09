#include <stdio.h>

int main(void) {
   int size;
   int threshold;
   int count = 0;

   printf("How many integers to enter?\n");
   scanf("%d", &size);
   
   int array[size];
   
   if (size > 1) {
       printf("Please enter %d integers: \n", size);
   }
   else{
       printf("Please enter %d integer: \n", size);
   }
   
   for (int i = 0; i < size; ++i) {
      scanf("%d", &(array[i]));
   }
   printf("Enter threshold: \n");
   scanf("%d", &threshold);
   
   for (int i = 0; i < size; ++i) {
      if (array[i] <= threshold) {
         if (count == 0) {
            printf("%d", array[i]);
            count++;
         }
         else {
            printf(", %d", array[i]);
         }
      }
   }
   printf("\n");

   return 0;
}