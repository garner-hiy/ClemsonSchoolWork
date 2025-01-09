#include <stdio.h>
#include <stdio.h>
/*  The ^ in [^\n] is a special character.  This says read until you see a new line
     *character[^*] :- It will stop reading only when a * is entered.
     *[^~] :- It will stop reading only when a tilde(~) is entered.
     *[^k] :- It will stop reading only when a lowecase character 'k' is entered.
     *[^9] :- It will stop reading only when the digit 9 is entered.
     *[^(0-9)]:-It will stop reading only when any digit is entered.
     *[^*~?] :- It will stop reading only when * or ~ or ? is entered.
    */

int main()
{
    char str[100];
    printf("Enter a string in lower case: \n");
    scanf("%[a-z]", str);
    printf("The string you entered: %s\n", str);
    printf("Enter a string in upper case: \n");
    scanf(" %[A-Z]%*c", str );//([]%*c) if there is a comma, it will skip it and put the pointer on the next character
    printf("The string you entered: %s\n", str);
    /*printf("Enter a string with a combination of upper, lower, and numbers: \n");
    scanf("%[a-z,A-Z,0-9]%*c", str );
    printf("The string you entered: %s\n", str);
    printf("Enter a string with a combination of upper, lower,numbers and spaces: \n");
    scanf("%[a-z,A-Z,0-9,' ']%*c",str);
    printf("The string you entered: %s\n", str);
    printf("Enter a string with a combination numbers: \n");
    scanf("%[0-9]%*c",str);
    printf("the numbers you entered: %s\n", str);
    printf("Enter a string terminated with a return: \n");
    scanf("%[^\n]%*c", str);
    printf("The string you entered: %s\n", str);*/

    /*
     *What if I want to read until I see  '-' but I had a series of these
     *today-is-friday
    */

    char a[15];
    char b[15];
    char c[15];
    char d[15];

    printf("Enter 4 sets of chars,nums, separted with - : \n");
    /*the ^ says read any set of characters until you see the -
    *the %*c  says to read a character but discard it. You can also type the 
    *character it is looking for - in this case and it will ignore it
    *
    * What happens if we do not put - in between the first two reads
    */
    scanf("%[^-]-%[^-]%*c%[^-]%*c%[^\n]%*c", a, b, c, d);
    printf("Strings: %s, %s, %s, %s\n", a, b, c, d);

    return 0; 

}
