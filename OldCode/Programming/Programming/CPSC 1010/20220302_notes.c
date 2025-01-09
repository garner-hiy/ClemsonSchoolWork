//Array notes and code

//declaring an array (no values)
int array[20];
int array1[size of array]; //gotta include a size 
double array2[20];
bool array3[20];
char string[20];

//declaring an array (with initial values)
int array[5] = {1, 2, 3, 4, 5};
char string[] = "Hi computer science is awesome!";

//initializing an array that has already been declared
for (int i = 0; i< 20; ++i){
    array[i] = 0;
}

//reading input into an array
for (int i = 0; i < 20; ++i){
    scanf("%d", &array[i]);
}

//copying an array
int newArray[20];
for (int i = 0; i < 20; ++i){
    newArray[i] = array[i];
}

//modifying an array
for (int i = 0; i < 20; ++i){
    newArray[i] = array[i] + 10;
}
for (int i = 0; i < 20; ++i){//shifts array over one
    if (i == 0){
        newArray[19] = array[i];
    }
    else {
        newArray[i - 1] = array[i];
    }
}

//printing an array
for (int i = 0; i < 20; ++i){
    printf("%d", array[i]);
}