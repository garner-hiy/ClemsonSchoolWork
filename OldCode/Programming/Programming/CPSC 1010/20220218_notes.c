/*  WHile Loop


while (condition expression is true){
    do somthing - loop body


}
*/

#include <stdio.h>

int main (void)
{
    int userNum;
    int max;
    
    scanf("%d", &userNum);
    max = userNum;

    while (userNum >= 0) {
        if (userNum > max){
            max = userNum;
        }
        scanf("%d", &userNum);
       
    }
    
    printf("%d", max);


    return 0;
}
