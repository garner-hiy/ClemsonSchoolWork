/*************************
*AJ Garner
*Kannniese Chen
*CPSC 2311 001
*adgarne@g.clemson.edu
*************************/
#include "src/functions.h"

int main(int argc, char* argv[]){
    //this is making the file pointers
    FILE *input, *output;
    //these 2 lines will open the files in the proper modes
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    //assert will determine if input is open
    assert(input != NULL);

    //these will call the functions
    numSentences(input, output);
    numWords(input, output);

    //these will close the files
    fclose(input);
    fclose(output);
    

    return 0;
}
