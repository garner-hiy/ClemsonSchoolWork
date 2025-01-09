/*

output is 
0
 1
  2
   3


#include <stdio.h>

int main(void) {
   int userNum;
   int i;
   int j;

   scanf("%d", &userNum);

   for (i = 0; i <= userNum; ++i) {
    for (j = 0; j < i; ++j){
       printf(" ");
    }
    printf("%d\n", i);
   }

   return 0;
}



Outputs

1A 1B 1C 2A 2B 2C 

#include <stdio.h>

int main(void) {
   int numRows;
   int numColumns;
   int currentRow;
   int currentColumn;
   char currentColumnLetter;

   scanf("%d", &numRows);
   scanf("%d", &numColumns);

   for (currentRow = 0; currentRow < numRows; ++currentRow) {
      currentColumnLetter = 'A';
    for(currentColumn = 0; currentColumn < numColumns; ++currentColumn){
     printf("%d%c ", currentRow + 1, currentColumnLetter); 
     currentColumnLetter++;
    }
   }

   printf("\n");

   return 0;
}


output

Testing simonPattern: RRGBRYYBGY and userPattern: RRGBBRYBGY
Your output
userScore: 4

#include <stdio.h>
#include <string.h>

int main(void) {
   char simonPattern[50];
   char userPattern[50];
   int userScore;
   int i;

   userScore = 0;

   scanf("%s", simonPattern);
   scanf("%s", userPattern);

  for (i = 0; simonPattern[i]; i++) { 
       if (simonPattern[i] == userPattern[i]) { 
          userScore++;
       }
       else{
          break;
       }
    }

   printf("userScore: %d\n", userScore);

   return 0;
}
*/