#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main (void){

    char userPhrase[50];
    char userAcronym[50];
    printf("Enter a word or phrase (maximum 50 characters):\n");
    scanf("%[^\n]s", userPhrase);
    printf("%s\n", userPhrase);
    

int j = 0;    
for(int i = 0; i < strlen(userPhrase); ++i){
        if(isupper(userPhrase[i])){
            
            userAcronym[j] = userPhrase[i];
               userAcronym[j + 1] = '.';
              ++j;
              ++j;
            
            //for(int j = 0; j < strlen(userPhrase); ++j){
            //    userAcronym[j] = userPhrase[i];
           //     userAcronym[j + 1] = '.';
            //    ++j;
            //}
        }
        
    }
    userAcronym[j] = '\0';
    printf("%s\n", userAcronym);
    return 0;
}