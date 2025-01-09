#include <stdio.h>
// function prototypes

int add(int x, int y);
int subtract(int x, int y);
/*This function take a function pointer as a parameter.  In this case the
 *two other parameters are the values used when the function pointer is
 *executed*/
int domath(int (*mathop)(int, int), int x, int y);

// calling from main
int main() 
{
  // call math function with add
  int a = domath(&add, 10, 2);
  printf("Add gives: %d\n", a);

  // call math function with subtract
  int b = domath(subtract, 10, 2);
  printf("Subtract gives: %d\n", b);
}

// add x + y
int add(int x, int y) {
  return x + y;
}

// subtract x - y
int subtract(int x, int y) {
  return x - y;
}

// run the function pointer with inputs
int domath(int (*mathop)(int, int), int x, int y) {
	/*This is where the funtion pointer is called (again this can be called using
    (*mathop) (x,y) or without the '*' (mathop)(x,y))*/

  return mathop(x, y);
}
