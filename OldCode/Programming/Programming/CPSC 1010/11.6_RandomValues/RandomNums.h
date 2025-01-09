#ifndef RANDOMNUMS_H_
#define RANDOMNUMS_H_

typedef struct RandomNumsStruct_struct{//this is the struct
   int var1;//random value stored here
   int var2;//random value stored here
   int var3;//random value stored here
}RandomNums;//struct type

RandomNums SetVals(int low, int high);//prototype in RandomNums.c

void GetVals(RandomNums r);//another prototype in RandomNums.c

#endif
