/* printf example */
#include <stdio.h>

int main()
{
   /*two ways to print the character a - using ' ' and ascii value*/
   printf ("Characters: %c %c \n", 'a', 65);
   /*Characters: a A */

   //int and long integer
   printf ("Decimals: %d %ld\n", 1977, 650000L);
   /*Decimals: 1977 650000*/

   //value is preceded with blanks (length is 10) width
   printf ("Preceding with blanks: %10d\n", 1977);
   /*Preceding with blanks:       1977*/

   //value is preceded with 0's (length is 10)
   printf ("Preceding with zeros: %010d\n", 1977);
   /*Preceding with zeros: 0000001977*/

   //value printed in different bases last two preceed with 0x and 0 respectively
   printf ("Some different radices %d %x %o %#X %#o \n", 100, 15, 100, 15, 100);
   /*Some different radices 100 f 144 0XF 0144*/

   /*floating point printed first in hex because of the (A)-width of 4 precision 
    *of 6 hex (3 bytes) second width 4 precision of 2, 
    *third no width specified 0 precision the + forces the positive sign to print
    *fourth no formating specified so default of precision (6digits) */
   printf ("floats: %4.6A %4.2f %.0e %E \n", 3.1416, 53.1416, +0.0, 3.141599999);
   /*floats: 0X1.921FF3P+1 53.14 +0e+00 3.141600E+00
    *Change 0.0 to -0.0 floats: 0X1.921FF3P+1 53.14 -0e+00 3.141600E+00
    *if 0.0 has no signed: floats: 0X1.921FF3P+1 53.14 0e+00 3.141600E+00 
    */


   /* says I am going to add the width in the parameter list 5 indicates the
    *width is 5 so this prints 3 spaces and the numbers 10 give a width of 5
    *%.*d will addd 0's rather just spaces*/ 
   printf ("Width trick:%*d \n", 5, 10);
   /*Width trick:   10*/

   //No explanation needed here
   printf ("%s\n", "A string");
   /*A string*/
   return 0;
}

