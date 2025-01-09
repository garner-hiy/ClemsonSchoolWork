#include <stdio.h>
struct date {
	int d : 5; //Range is -16 to 15 day must have a value of at least 31
	int m : 4; //Range is -8 - 7 month must have a value of at least 12
	int y; 
}; 

int main() 
{ 
	printf("Size of date is %lu bytes\n", sizeof(struct date));
	struct date dt = { 31, 12, 2020 }; 
	printf("Date is %d/%d/%d\n", dt.d, dt.m, dt.y); 
	return 0; 
}
