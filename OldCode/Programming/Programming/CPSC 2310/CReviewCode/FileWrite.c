#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[])
{
    /*I could use "w" but because I am using fwrite it will write 
     * in binary mode anyway.  */
    FILE* out = fopen(argv[1], "wb");
    assert(out != NULL);
    /*fprintf is designed to print human readable not binary.  So even though I 
     *used b when opening the output file pointer, fprintf printed in readable
     *format rather than binary. */
    fprintf(out, "Hello World\n");

    char buf[] = "This is going to be a great day!!"; 

    /*Syntax: size_t fwrite(const void *ptr, size_t size, size_t n, FILE *fp);
     *used to write in binary format. I will sometime use fwrite and fread when
     *working with ppm files since the RGB values of a P6 image is binary format
     *rather than text. Fwrite writes whole blocks at a time
     *fread reads whole blocks at a time.  It also reads binary format as well. 
     *Reading and writing in binary format is faster.  
     */
    /*Change 1 to 2 and see what happens*/
    fwrite(buf, sizeof(buf),1, out);
 
    return 0;
}