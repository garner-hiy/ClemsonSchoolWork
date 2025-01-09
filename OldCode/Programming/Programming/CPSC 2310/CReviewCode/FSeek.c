
#include <stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("fseek.txt", "r");
	printf("printing the position of the file pointer prior to calling fseek" 
    " %ld\n", ftell(fp));
	// Moving pointer to end
	fseek(fp, 0, SEEK_END);
    printf("moving to the end of the file %ld\n", ftell(fp));
    //fseek(fp, 5, SEEK_SET);
    // Moving pointer 5 space beyond the end of the file.
	fseek(fp, 5, SEEK_CUR);
    printf("moving 5 spaces beyond the file %ld\n", ftell(fp));
    
    //Moving pointer 7 places before the end 
    fseek(fp, -7, SEEK_END);
    printf("moving 7 places before the end %ld\n", ftell(fp));

    /*Here I am setting the file to the beginning of the file.  I can use
     *fseek or rewind, both will set the file pointer to position 0 in the array 
     *of Characters. */
	fseek(fp, 0, SEEK_SET);
    //rewind(fp);
	// Printing position of pointer
	printf("Setting the pointer to the beginning of the file %ld\n", ftell(fp));

	return 0;
}
