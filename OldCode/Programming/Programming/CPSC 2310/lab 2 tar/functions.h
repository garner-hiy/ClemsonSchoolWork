/*************************
*AJ Garner
*Kannniese Chen
*CPSC 2311 001
*adgarne@g.clemson.edu
*************************/

#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/*This function numSentences will read in an input
and an output file. It will count the charaters at
the end of the sentences and use a count variable
to count how many sentences there are in the input
file.
It will output that information to an output file
and end the funtion.
*/
void numSentences(FILE* in, FILE* out);

/*This function numWords will read in an input
and an output file. It will count the white space
as well as the and use a count variable
to count how many sentences there are in the input
file.
It will output that information to an output file
and end the funtion.
*/
void numWords(FILE* in, FILE* out);


#endif
