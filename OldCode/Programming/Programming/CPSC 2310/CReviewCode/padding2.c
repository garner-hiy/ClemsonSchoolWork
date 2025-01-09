#include <stdio.h> 
#include <stdlib.h>
typedef struct test
{
    char a;
    short b;
    int c;
    char d;
    float e;  
}test_t;

typedef struct test2
{
    int a;
    short int b;
    char c;
    char d;
}test2_t;

int main()
{
    test_t test1;
    test2_t test2;  
    printf("Size of test1: %zu \n", sizeof(test1));
    printf("a = %p\nb = %p\nc = %p\nd = %p\ne = %p\n\n", 
    &test1.a, &test1.b, 
    &test1.c, &test1.d,
    &test1.e);

    printf("Size of test2: %zu \n", sizeof(test2));
    printf("a = %p\nb = %p\nc = %p\nd = %p\n", 
    &test2.a, &test2.b, 
    &test2.c, &test2.d);    
    return 0; 
}
/*
Size of test1: 12                   Size of test2: 8 
a = 0x7ffee84eb830                  a = 0x7ffee84eb828
b = 0x7ffee84eb834                  b = 0x7ffee84eb82c
c = 0x7ffee84eb838                  c = 0x7ffee84eb82e
d = 0x7ffee84eb83a                  d = 0x7ffee84eb82f
*/
