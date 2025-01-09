#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "RandomNums.h"

int main() {
	srand(time(0));   // Set seed value for random numnbers.

	int low;
	int high;

	scanf("%d", &low);
	scanf("%d", &high);

	RandomNums r = SetVals(low, high);
	
	GetVals(r);

	return 0;
}