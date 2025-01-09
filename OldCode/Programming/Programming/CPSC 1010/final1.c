#include <stdio.h>

int main(int argc, char* argv[]) {          
   
   printf("Arguments passed: %d\n", argc);
   if (argc != 4) {
      printf("Usage: myprog.exe argument1 argument2 argument3\n");
      return 1; 
   }
  for(int i = 0; i < argc; ++i){
     printf("argv[%d] = %s\n",i, argv[i]);
  }

   return 0;

}