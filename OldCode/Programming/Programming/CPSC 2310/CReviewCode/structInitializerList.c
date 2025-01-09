#include <stdio.h>

struct simple
{
    int a;
    char b;
    float c;
};
struct Init_Ex
{
    int a;
    short b[10];
    struct simple c;
}test = {20, {1,2,3,4,5},{25, 'Y', 2.5}};

int main()
{
    struct Init_Ex test2 = {20, {1,2,3,4,5},{25, 'Y', 2.5}};
    printf("%d %d %d %c %f\n", test.a, test.b[6], test.c.a, test.c.b, test.c.c);
    printf("%d %d %d %c %f\n", test2.a, test2.b[0], test2.c.a, test2.c.b, test2.c.c);
    return 0;
}