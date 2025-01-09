#include <stdio.h>
#include <stdlib.h>

#include "RandomNums.h"


RandomNums SetVals(int low, int high){
   RandomNums r;//variable used for storing the values
   r.var1 = (rand() % (high - low + 1)) + low;//equation needed to get proper number in range
   r.var2 = (rand() % (high - low + 1)) + low;
   r.var3 = (rand() % (high - low + 1)) + low;
   return r;//returns the struct
}

void GetVals(RandomNums r){//this is just for printing out the struct
   printf("Random values: %d %d %d\n", r.var1, r.var2, r.var3);
}

int GetVar1(RandomNums r){//unit test
   return r.var1;
}

int GetVar2(RandomNums r) {//unit test
   return r.var2;
}

int GetVar3(RandomNums r){//unit test
   return r.var3;
} 