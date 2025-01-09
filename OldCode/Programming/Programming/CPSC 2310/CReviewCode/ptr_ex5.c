#include <stdio.h>

int main()
{
    float arr[5] = {12.5, 10.0, 13.5, 90.5, 0.5};
    float *ptr1 = &arr[0]; // float *prt1 = arr; is the same

    /*Basically think of this as calculating what subscript I need to go to.
     *In order to do this the computer will also calculate the memory address by
     *using the sizeof the data type.  In this case the rhs is calculated first
     */
    float *ptr2 = ptr1 + 3;

    /*What will print here?*/

    printf("%.2f\n", *ptr2);

    /*This is calculating the subscript and printing the subscript not
     *printing the value at that subscript.  ptr2 is pointing at subscript 3
     *ptr1 is pointing to subscript 0 (3 - 0 = 3)*/
    printf("%ld\n", ptr2 - ptr1);
    /*to show it is calculating the subscript I am using this notation to
    *print from arr and ptr1*/
    printf("%.2f %.2f \n", arr[3], ptr1[(ptr2 - ptr1)]);
    /*I am printing the address of arr[3].  ptr1 is pointing to arr[0]
     *ptr2 is pointing to arr[3]
     *Each element in arr is 4 bytes in size.  when I subtract ptr2 - prt1 I get 
     *12 this means they are 12 bytes apart.  Since each element is 4 bytes in 
     *size then ptr2 is pointing to subscript 3  (12/4 = 3)*/
    int i = 0;
    for(i = 0; i < 5; i++)
    {
        printf("subscript %d's address = %p\n", i, &arr[i]);
    }
   return 0;
}
