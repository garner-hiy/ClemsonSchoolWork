#include <stdio.h>

int main(void) {
   int NUM_VALS;
   int userNums[NUM_VALS];
   

   printf("How many integers to enter?\n");
   scanf(" %d", &NUM_VALS);

   if (NUM_VALS > 1) {
       printf("Please enter %d integers: \n", NUM_VALS);
   }
   else{
       printf("Please enter %d integer: \n", NUM_VALS);
   }
   for (int i = 0; i < NUM_VALS; ++i) {
      scanf(" %d", &(userNums[i]));
   }
    printf("Integers in reverse: ");
   for (int i = NUM_VALS - 1; i >= 0; --i) {
      printf("%d", userNums[i]);
      if (userNums[i] != userNums[0]) {
          printf(", ");
      }
   }
   
    printf("\n");

   return 0;
}