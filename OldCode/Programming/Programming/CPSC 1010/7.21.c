#include <stdio.h>
#include <math.h>

int main (void){
    int num1;// first a*x
    int num2;// first b*y
    int num3;// first answer
    int num4;//second a*x
    int num5;//second b*y
    int num6;//second answer
    int x;
    int y;
    int answerx = x;
    int answery = y;
    char end;

    while (end != 'q'){// used to check if user wants to run again
//----------------------------------------------------------------------------------
    printf("Provide 6 integer coefficients for the brute force equation solver: \n");
    scanf("%d %d %d\n %d %d %d", &num1, &num2, &num3, &num4, &num5, &num6);

        for(int i = -10; i < 11; i++){//brute force loop
            for(int j = -10; j < 11; j++){//brute force loop
                if(num1 * i + num2 * j == num3 && num4 * i + num5 * j == num6){// a*x+b*y=answer
                y = j;
                x = i;  
                }
            }
        }
//---------------------------------------------------------------------------------
        if ((answerx != x) && (answery != y)){// used to check if values are true
            printf("Solution found: x = %d, y = %d\n\n", x, y);
        }
        else{
            printf("There is no solution\n\n");
        } 
 //-----------------------------------------------------------------------------------   
    printf("Run program again? Type 'q' to quit or any other key to continue: \n\n");
    scanf(" %c", &end); // input to run again, must have space before % to pause program
    }

    return 0;
}