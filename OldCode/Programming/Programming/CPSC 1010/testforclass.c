#include <stdio.h>
#include <math.h>

int main(void) {

   double r;
   double n;
   
   r = pow(2.0, 1.0 / 12.0);
   
   scanf("%lf", &n);
   printf("%0.2lf ", n);
   
   for (int i = 1; i < 5; ++i){
      double count = 1.0;
      n = n * pow(r, count);
      printf("%0.2lf ", n);
      count += 1.0;
   }
   printf("\n");
   return 0;
}