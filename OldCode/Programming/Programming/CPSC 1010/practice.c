#include <stdio.h>
#include <string.h>

int main(void) {

   int rows;
   scanf("%d", &rows);
   char array[rows][20];
   for(int i = 0; i < rows; ++i){
       scanf("%s", array[i]);
       printf("%s ", array[i]);
   }

   return 0;
}