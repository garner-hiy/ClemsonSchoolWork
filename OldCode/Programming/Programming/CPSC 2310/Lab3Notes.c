//use atoi() to convert char to int
//use [^,] to read in the data
#include <stdio.h>

 

int main()

{

    float arr[5] = {18.5, 90.5, 13.5, 10.8, 0.5};

    float *ptr1 = &arr[0];

    float *ptr2 = ptr1 + 3;

 

    printf("%.2f\n", *ptr2);

    printf("%ld\n", ptr2 - ptr1);

    printf("%.2f \n", ptr1[(ptr2 - ptr1)]);

    int i = 0;

   
printf("Unusual trick: %*d\n", 5, 10);
   return 0;

 }