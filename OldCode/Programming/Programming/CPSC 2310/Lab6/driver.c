/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
*email: adgarne@clemson.edu*
*************************/
#include "functions.h"


int main(int argc, char* argv[]){
    //check that there are enough command line arugments
    assert(argc < 4);

    //this is making the file pointers
    FILE *input, *output;

    //these 2 lines will open the files in the proper modes
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    //assert will determine if input and output is open
    assert(input != NULL);
    assert(output != NULL);

    //needed to start the linked list
    node_t *head = NULL;
    
    //call to funations
    createList(input, &head);

    list_stats_t stats = getListStats(head);
    
    printStats(output, &stats);
    
    deleteList(&head);

    //need to close files before returning due to memory leaks
    fclose(input);
    fclose(output);

    return 0;
}