#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char str[100];

    FILE* test = fopen(argv[1], "r");

    /*%[^\n] means scanf will read until it encounters a newline character.
     *http://www.cplusplus.com/reference/cstdio/scanf/ 
     */

    /*The 9 in the following line of code tells Mr. compiler that you only want 
     *read 9 characters.  Why do you think I chose 9??  Perhaps because the size
     *of str array is 10 you need one element of the array for the null 
     *charager
     */

    //Run with goodTest.txt and test.txt
    
    fscanf(test, "%9[^\n]", str);
    printf("%s\n", str);
    /*The next two lines say read until you see a new line character then discar
     *the new line character*/
    fscanf(test, "%[^\n]%*c", str);
    //fscanf(test, "%[^\n]\n", str);
    printf("%s\n", str);

    return 0;

}