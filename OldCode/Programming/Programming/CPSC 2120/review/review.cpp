#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include <bits/stdc++.h>
#include "review.h"
using namespace std;


void ReadStdIn(){
   int a;
   double b;
   string word;
   cin >> a >> b >> word;
   cout << a << endl << b << endl << word << endl;
}

int WriteOut(std::string output){
   cout << output;
   return 1;   
}

int WriteOut(int output){
   cout << output;
   return 2;
}

int WriteOut(double output){
   cout << output;
   return 3;
}

void ReadStdIn2(){
   string stuff;
   int count = 0;
   while (stuff != "q"){
      cin >> stuff;
      ++count;
   }
      
   cout << count - 1;
}


void ReadWrite(){
   string stuff, bigStuff;
   while (stuff != "q"){
      cin >> stuff;
      bigStuff = bigStuff + ' ' + stuff;
   }
   bigStuff.pop_back();
   bigStuff.erase(bigStuff.begin());
   cout << bigStuff;
   
}

void LoopThrough(double * data, int size){
   for(int i = 0; i < size; ++i){
      data[i] = data[i] + 1;
   }
}


int Fibonacci(int a){
   if (a <= 1)
   return a;
   else
   return Fibonacci(a-1) + Fibonacci(a-2);
}

vector <int> InitializeArray(int size){
   vector <int> re;
   for(int i = 0; i < size; i++){
      re.push_back(i * 0);
   }
   return re;
}
