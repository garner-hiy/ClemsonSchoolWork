#include <stdio.h>


void Swap(int& x, int y) {
   int tmp;
   tmp = x;
   x = y;
   y = tmp;
}


int main(void) {
   int p = 4, q = 3;
   Swap(p, q);
   printf("p = %d, q = %d\n", p, q);
   return 0;
}