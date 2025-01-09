
#include<stdio.h>
void f(int *p, int *q)
{
  //printf("inside f ; p is pointing to this address %p\n", p);
  //printf("inside f ; q is pointing to this address %p\n", q);
  p = q; 
  //printf("inside f and after p = q ; p is pointing to this address %p\n", p);
  *p = 2;
}

int main()
{
  int i = 0, j = 1;
  int *ip = &i;
  int *ij = &j;
  //printf("Before calling f - ip is pointing to this address %p\n", ip);
  
  f(ip, ij);
  //printf("After calling f - ip is pointing to this address %p\n", ip);
  printf("%d %d and %d %d\n", i, j, *ip, *ij);

  
  return 0;
}

/*What is the output of the above?





*/
