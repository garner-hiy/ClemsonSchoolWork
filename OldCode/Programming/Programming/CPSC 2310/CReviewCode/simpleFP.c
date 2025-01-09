#include <stdio.h>

/*Function prototypes to use with the function pointer*/
void printNum(int);
void numSq(int);
int adder(int, int);

int main(int argc, char* argv[])
{
  /*I am declaring a variable of type void pointer that will point to a function
   *that has one int as the parameter.  Must have the () around the pointer.*/
  void (*fp)(int)= numSq;
  fp(10);
  /*Here is another way you point a function pointer to a function.
   *Could have set fp = &printNum, but using the & is optional. This is
   *basically initializing the function pointer to point to a function.
   *Just like a regular pointer */
  fp = printNum;
  /*Now that fp is pointing to a function you can just call that function
   *using the function pointer.*/
  fp(15);
  //or
  /*must put () around the dereferencing/indirection*/
  (*fp)(20);

  /*This function pointer must point to a function that returns an int and
   *has two parameters of type int*/
  int (*fp2) (int, int);

  /*Now I am going to point fp2 to a function that returns an int and has
   *two integers as paramters*/
  fp2 = adder;

  /*This is a call to fp2 passing in two parmeters.  since adder has a return
   *value I created sum so I can have a variable to catch the return from
   *adder*/
  int sum = fp2(5, 10);

  /*I can also use fp that is currently pointing to printNum to print the value
  *of sum.*/
  fp(sum);

  printf("Sum = %d\n", sum);

  return 0;
}

void printNum(int n)
{
  printf("The number is %d\n", n);
}

void numSq(int n)
{
  printf("The square of n (%d) is %d\n",n, n*n);
}

int adder(int a, int b)
{
  return (a + b);
}
