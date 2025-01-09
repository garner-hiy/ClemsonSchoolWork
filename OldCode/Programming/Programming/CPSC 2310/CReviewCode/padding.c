#include <stdio.h>
#include <string.h>
 /*  Below structure1 and structure2 are same. 
    They differ only in member's allignment */
 struct structure1 
{
       int id1;
       int id2;
       char name;
       char c;
       float percentage;
};
struct structure2 
{
       int id1;
       char name;    
       int id2;
       char c;
       short percentage;                      
};
struct structure3 
{
       char name;
       char c;
       int id1;
       int id2;
       float percentage;                      
};
struct structure4 
{      
       char id1;
       char id2;
       char name;
       char c;
       char percentage;
};

int main() 
{
    struct structure1 a;
    struct structure2 b;
    struct structure3 c;
    struct structure4 d;
    
    printf("size of structure1 in bytes : %lu\n", sizeof(a));
    printf ( "\n   Address of id1        = %p", &a.id1 );
    printf ( "\n   Address of id2        = %p", &a.id2 );
    printf ( "\n   Address of name       = %p", &a.name );
    printf ( "\n   Address of c          = %p", &a.c );
    printf ( "\n   Address of percentage = %p\n", &a.percentage );
 
    printf("   \n\nsize of structure2 in bytes : %lu\n",sizeof(b));
    printf ( "\n   Address of id1        = %p", &b.id1 );
    printf ( "\n   Address of name       = %p", &b.name );
    printf ( "\n   Address of id2        = %p", &b.id2 );
    printf ( "\n   Address of c          = %p", &b.c );
    printf ( "\n   Address of percentage = %p\n\n",&b.percentage );

    printf("size of structure3 in bytes : %lu\n", sizeof(c));
    printf ( "\n   Address of name       = %p", &c.name );
    printf ( "\n   Address of c          = %p", &c.c );
    printf ( "\n   Address of id1        = %p", &c.id1 );
    printf ( "\n   Address of id2        = %p", &c.id2 );
    printf ( "\n   Address of percentage = %p\n\n",&c.percentage );

    printf("size of structure4 in bytes : %lu\n", sizeof(d));
    printf ( "\n   Address of id1        = %p", &d.id1 );
    printf ( "\n   Address of id2        = %p", &d.id2 );
    printf ( "\n   Address of name       = %p", &d.name );
    printf ( "\n   Address of c          = %p", &d.c );
    printf ( "\n   Address of percentage = %p\n", &d.percentage );       
    return 0;
}

/*
size of structure1 in bytes : 16

   Address of id1        = 0x7ffee4daa828
   Address of id2        = 0x7ffee4daa82c
   Address of name       = 0x7ffee4daa830
   Address of c          = 0x7ffee4daa831
   Address of percentage = 0x7ffee4daa834
   

size of structure2 in bytes : 20

   Address of id1        = 0x7ffee4daa810
   Address of name       = 0x7ffee4daa814
   Address of id2        = 0x7ffee4daa818
   Address of c          = 0x7ffee4daa81c
   Address of percentage = 0x7ffee4daa820

size of structure3 in bytes : 16

   Address of name       = 0x7ffee4daa800
   Address of c          = 0x7ffee4daa801
   Address of id1        = 0x7ffee4daa804
   Address of id2        = 0x7ffee4daa808
   Address of percentage = 0x7ffee4daa80c

size of structure4 in bytes : 5

   Address of id1        = 0x7ffee4daa7f8
   Address of id2        = 0x7ffee4daa7f9
   Address of name       = 0x7ffee4daa7fa
   Address of c          = 0x7ffee4daa7fb
   Address of percentage = 0x7ffee4daa7fc

*/