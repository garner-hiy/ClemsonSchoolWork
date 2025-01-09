#include <stdio.h>
//double pointer example
int f(int , int *, int **);

int  main()
{
   int c, *b, **a;
   c = 7;
   b = &c;
   a = &b;

   /*If you want to see the address of a variable you can use %p.  Of course the
   value of a pointer is also an address, so if you want to print the value of
   a pointer you should also use %p*/
  // printf("Address of: a = %p, b = %p, c = %p\n", &a, &b, &c);
  // printf("Value of a is: %p\n", a);
   printf("%d \n", f(c, b, a));
   /*This goes to where a is pointing and prints the value*/
   //printf("%p = a\n", *a);
   //printf("value of b: %p\n", b);
   //printf("%p = b\n", &b);
   return 0;
}

int f(int x, int *py, int **ppz)
{
  /*This prints the value of ppz aka 'a'. 'a' has the value of the address
   *of what it is pointing to which is 'b'.  We know it is going to print an
   *address because in c %p represents an address*/


  //printf("%p = ppz\n", ppz);

  int y, z;
  /*This is a double dereference here.  This says go to where ppz (a) points
   *which is (b) then go to where 'b' is pointing and add two to that the
   *value */
  // is the same (**ppz) += 1; or **ppz is fine as well
  (*(*ppz)) += 8;

  /*'z' is a local variable:  now go to where ppz is pointing then go to where
   *b is pointing which is c and set z equal to that value. What is this value?*/
   z  = **ppz;
   /*This says go to where py (b) is pointing (c) and add 6 to it.  This will
    *change the value of c*/
  *py += 5;
  /*'y' is a local variable. This says set y equal to the the value of what
   *'py' is pointing 'c'*/
   y = *py;
   /*'x' is passed the value of 'c'.  Add 1 to 'x'*/
   x += 2;
   /*What is being returned.*/
   return x + y + z;
}
