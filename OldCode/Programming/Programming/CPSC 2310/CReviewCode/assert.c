#include <stdio.h>
#include <assert.h>
 
int main()
{
    int x = 7;
    x = 9;   
    assert(x==7);

    return 0;
}