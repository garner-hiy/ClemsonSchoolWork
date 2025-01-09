#include <stdio.h>
#include <stdbool.h>

int main(void) {
   int size;
   int count = 0;
   int lower;
   int upper;
   bool inRange = false; //needed to check if there are integer in the boundries
////////////////////////////////////////////////////////////////////////////////////////////
//dashes are used to break up the code into sections to more easily read

   printf("How many integers to enter?\n");
   scanf("%d", &size);
////////////////////////////////////////////////////////////////////////////////////////////  

   int array[size]; //should be declared after getting size
////////////////////////////////////////////////////////////////////////////////////////////

   if (size > 1) { //used to see if there are more than one integer
       printf("Please enter %d integers: \n", size);
   }
   else{
       printf("Please enter %d integer: \n", size);
   }
///////////////////////////////////////////////////////////////////////////////////////////

   for (int i = 0; i < size; ++i) {// used to collect elements
      scanf("%d", &(array[i]));
   }
   printf("Lower and upper bounds: \n");//used to determine bounds
   scanf("%d%d", &lower, &upper);
//////////////////////////////////////////////////////////////////////////////////////////// 

   for (int i = 0; i < size; ++i) {//loops to check array elements
      if (array[i] <= upper && array[i] >= lower) {
         if (count == 0) {
             inRange = true;
            printf("Elements in range: %d", array[i]);
            count++;
         }
         else {//needed to print commas correctly
            printf(", %d", array[i]);
         }
      }
   }
////////////////////////////////////////////////////////////////////////////////////////////
   
   if (inRange == false) {//used if there are no elements in range
         printf("Elements in range: no values in range");
         }
////////////////////////////////////////////////////////////////////////////////////////////
   
   printf("\n");

   return 0;
}