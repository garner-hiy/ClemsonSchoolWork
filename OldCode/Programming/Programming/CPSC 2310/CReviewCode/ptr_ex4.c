#include <stdio.h>


int main()
{

   /*Can you think of a reason why you might want to have a pointer to an
   Array*/
    
    int iArr[] = {1, 2 ,3};
    int *iPtr = iArr;
    char cArr[] = {64, 'A' , 98}; //64 = @ 98 = b 65 = A
    char *cPtr = cArr;

    /*The size of an int depends on the computers architecture.  For my laptop
     *an int is 4 bytes so 4 * 3 = 12 bytes. However, a pointer to an int iPtr
     *is 8 bytes*/
    printf("sizeof [] = %lu \n", sizeof(iArr));
    printf("sizeof iPtr = %lu \n", sizeof(iPtr));

    /*Characters are only one byte of data so the total size of cArr is
     *3 * 1 = three bytes*/
    printf("sizeof cArr[] = %lu \n", sizeof(cArr));
    printf("sizeof cPtr = %lu \n", sizeof(cPtr));

    /*I can access these pointers using array notation or pointer arithmetic
     *I can also access the array itself using array notiatin and pointer
     *arithmetic*/

    /*When using array notation the [] acts the same as * with respect to
     *dereferencing*/
    printf("cPtr[0] = %c \n", cPtr[0]);
    printf("cArr[0] = %c \n", cArr[0]);
    printf("*cArr = %c \n", *cArr);
    printf("*(cPtr+1) = %c \n", *(cPtr+1));//cPtr[1]
    printf("*(cArr+1) = %c \n", *(cArr+1)); //cArr[1]
    printf("*(cPtr+1) + 1 = %c \n", *(cPtr+1)+1);//cPtr[1] +1
    printf("*(cArr+1) + 1 = %c \n", *(cArr+1)+1);//cArr[1] +1
    printf("*(cPtr+2) = %c \n", *(cPtr+2));//cPtr[2]
    printf("*(cArr+2) = %c \n", *(cArr+2));//cArr[2]

    printf("iPtr[0] = %d\n", iPtr[0]);
    printf("iPtr[0] + 1 = %d\n", iPtr[0] +1);
    printf("iPtr[1] = %d\n", *(iPtr+1));
    printf("iPtr[1] + 1 = %d\n", *(iPtr+1)+1);
    printf("iPtr[2] = %d\n", *(iPtr+2));

    return 0;
}

/*
sizeof [] = 12 
sizeof iPtr = 8 
sizeof cArr[] = 3 
sizeof cPtr = 8 
cPtr[0] = @ 
cArr[0] = @ 
*cArr = @ 
*(cPtr+1) = A 
*(cArr+1) = A 
*(cPtr+1) + 1 = B 
*(cArr+1) + 1 = B 
*(cPtr+2) = b 
*(cArr+2) = b 
iPtr[0] = 1
iPtr[0] + 1 = 2
iPtr[1] = 2
iPtr[1] + 1 = 3
iPtr[2] = 3
*/
