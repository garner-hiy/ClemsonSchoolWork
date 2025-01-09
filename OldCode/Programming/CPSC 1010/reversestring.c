 /*   
  

 //this is the over complicated version 
 int i, left, right, len;
    len = strlen(blank);//need the string length 
    left = 0;// for setting left index with 0
    right = len - 1; //set right index with len - 1
    for(i = left; i < right; i++){// this loop is needed to store reverse string
        temp = blank[i]; //need to assgin temp string with the blank string
        blank[i] = blank[right];
        blank[right] = temp;
        right--;
    }
 
 
 //this is a better way to reverse the string
    int j = 0;
    for (int i = strlen(original) - 1; i >= 0; --i){
        reversed[j] = original[i];
        ++j;
    }

    */