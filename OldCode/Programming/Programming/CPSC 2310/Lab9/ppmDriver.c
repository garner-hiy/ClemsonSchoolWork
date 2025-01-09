/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
*email: adgarne@clemson.edu*
*************************/
#include "ppmUtil.h"

int main(int argc, char* argv[]){

    //this is making the file pointers
    FILE *input, *output;

    //these 2 lines will open the files in the proper modes
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    //assert will determine if input and output is open
    assert(input != NULL);
    assert(output != NULL);

    //these are the two variables needed to store the data
    header_t head_data;
    pixel_t* pixels;

    //these are all the nessary function calls to the program
    pixels = read(input, &head_data);
    write(output, head_data, pixels);

    //this will free the memory
    freeMemory(pixels);

    //need to close files before returning due to memory leaks
    fclose(input);
    fclose(output);

    return 0;
}