#include <stdio.h>
/*https://stackoverflow.com/questions/5580761/why-use-double-pointer-or-why-use-pointers-to-pointers
*/

void cant_change(int * x, int * z);
void change(int ** x, int * z);
int main()
{
    int c = 1;
    int d = 2;
    int e = 3;

    printf("address of c: %p\n", &c);
    printf("address of d: %p\n", &d);
    printf("address of e: %p\n", &e);
    
    int * a = &c;
    int * b = &d;
    int * f = &e;
    int ** pp = &a;  // pointer to pointer 'a'
    printf("\n a's value: %p \n", a);
    printf("\n b's value: %p \n", b);
    printf("\n f's value: %p \n", f);
    printf("\n can we change a?, lets see \n");
    printf("\n a = b \n");
    
    /*Since a and b are both pointers yes we can do this*/
    a = b;
    printf("\n a's value is now: %p, same as 'b'... it seems we can, but can we do it in a function? lets see... \n", a);
    printf("\n cant_change(a, f); \n");
    cant_change(a, f);
    printf("\n a's value is now: %p, Doh! still same as 'b'...  that function tricked us. \n", a);
    /*Although a and f are both pointers when you pass a pointer to a function
     *with the expectation of changing the value of the pointer (not what the 
     *pointer is pointing to) then you have to pass a pointer to a pointer. 
     *The same principle of pass by value as opposed to pass by reference applies
     *in this instance. */
    printf("\n NOW! lets see if a pointer to a pointer solution can help us... remember that 'pp' point to 'a' \n");
    
    printf("\n change(pp, f); \n");
    change(pp, f);
    printf("\n a's value is now: %p, YEAH! same as 'f'...  that function \
ROCKS!!!. \n", a);

printf("%d %d %d\n", c, d, e);
    return 0;
}
/*I found this statement at the link cited above:
  If you want to use a function to modify a thing, be it an object or an address
  (pointer), you have to pass in a pointer to that thing. if not a pointer
  The thing that you
  actually pass in cannot be modified (in the calling scope) because a local
  copy is made.*/
void cant_change(int * x, int * z){
    x = z;
    printf("\n ----> value of 'a' is: %p inside function, same as 'f', BUT will\
it be the same outside of this function? lets see\n", x);
}

void change(int **x, int * z){
    *x = z;
    printf("\n ----> value of 'a' is: %p inside function, same as 'f', BUT will\
 it be the same outside of this function? lets see\n", *x);

}
