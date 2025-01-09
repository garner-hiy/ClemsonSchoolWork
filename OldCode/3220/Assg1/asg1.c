/*
Name: AJ Garner
Class: CPSC 3220

Purpose: The program will take in a "word" and a future date from the CL.
It will first check that the CL arguments are correct and give 3 tries before terminating.
It will also take the date and check that it is in the valid format.
It will use 2 child processes to preform different tasks.
Child 1 will print it's pid and it's parents pid, it will then run sha512hash.c.
Then Child 2 will print it's own pid and parents pid, it will then start a thread and 
calculate the difference between the current date and the future date.
Lastly it will print the difference.

This program does not account for leap years as according to instructions.

How to Compile Everything:
gcc sha512hash.c -o sha512hash -lcrypt
gcc asg1.c -o asg1 -pthread
./asg1 <word> <mm/dd/yyyy>

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <wait.h>
#include <stdbool.h>

//This is the strut used for storing the dates as integers
struct Date {
    int year;
    int month;
    int day;
};

//This is a helper function that will be used by the thread to find the
//difference between the future date and the current.
void* calculateDateDifference(void* arg) {

    //Storing the data passed in from the thread
    struct Date* argDate = (struct Date*)arg;

    //need to make a struct to store the results
    struct Date* differs = malloc(sizeof(struct Date));

    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    int CD = localTime->tm_mday;
    int CM = localTime->tm_mon + 1; //months start with 0, so need to add 1 to keep the integers correct
    int CY = localTime->tm_year + 1900; //need to add 1900 to correct the year as well

    //storing the difference
    differs->day = argDate->day - CD;
    differs->month = argDate->month - CM;
    differs->year = argDate->year - CY;

    //These if statements will account and adjust for the differences
    if (differs->day < 0) {
        // Adjust for negative days
        int daysInPrevMonth = 0;
        if (CM > 1) {
            daysInPrevMonth = 31;  // Assuming previous month has 31 days
        }

        differs->month--;
        differs->day += daysInPrevMonth;
    }
    if (differs->month < 0) {
        differs->year--;
        differs->month += 12;
    }

    //printing the thread id and then exit the thread
    printf("\tThread 1: tid %ld\n", pthread_self());
    pthread_exit(differs);
}

//This function will check to make sure that the date from the CL is acutally in the future
bool isDateFuture(int day, int month, int year){
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    if (year > localTime->tm_year + 1900 ||
        (year == localTime->tm_year + 1900 && month > localTime->tm_mon + 1) ||
        (year == localTime->tm_year + 1900 && month == localTime->tm_mon + 1 && day > localTime->tm_mday)) {
        return true;  // The date is in the future
    }
    else
        return false; //else it is not
}

//This function will check that the date is in the vaild format and it so,
//will pass the date to check that it is in the future.
bool isValidDate(char *dateString) {
    
    //these 4 lines are for parsing out the string to become an integer
    char temM[3];
    char temD[3];
    char temY[5];
    sscanf(dateString, "%2[^/]/%2[^/]/%4s", temM, temD, temY);

    //thses 4 lines will convert and store the integers
    int month, day, year;
    day = atoi(temD);
    month = atoi(temM);
    year = atoi(temY);
    

    // Checking for valid month, day, and year ranges
    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 2024) 
        return false;
    
    else if (!(isDateFuture(day, month, year)))
        return false; //if not in the future
    
    else
        return true; //if passed all checks
}



int main(int argc, char *argv[]) {
    char word[25]; //max word size
    char date[10]; //max size of date format
    struct Date dateSt; //date struct
    
    int i; //used for counting attempts
  
    //Checking for the correct number of arguments and that the date is valid
    if (argc != 3 || !(isValidDate(argv[2]))){
        for(i = 0; i < 3; ++i){
            printf("Try again. Please enter your <word>:\n");
            scanf("%s", word);
            printf("Now enter your future date <mm/dd/yyyy>:\n");
            scanf("%s", date);
            if(!(isValidDate(date))){
                continue;
            }
            else{
                break;
            }
        }
        if(i == 3){//If there are 3 tries, it will end the program with error -1
            printf("Too many tries.\n");
            return -1;
        }
    }
    else{ //if everything is good, just make the struct, parse the date, and store it
        strcpy(word, argv[1]);
        strcpy(date, argv[2]);

        //create the struct
        char temM[3];
        char temD[3];
        char temY[5];
        sscanf(date, "%2[^/]/%2[^/]/%4s", temM, temD, temY);
        dateSt.day = atoi(temD);
        dateSt.month = atoi(temM);
        dateSt.year = atoi(temY);

    }
     
    //First fork to start the first child process
    pid_t child1_pid = fork();
    
    //check to see that the child started
    if (child1_pid < 0){
        printf("child1 forking failed\n");
        return -1;
    }
    else if (child1_pid == 0){
        int pid = getpid();
        int ppid = getppid();

        printf("Child1: pid %d, ppid %d, ", pid, ppid);
        fflush(stdout);//need the child to wait and print the previous line first
        execvp("./sha512hash", argv);//runs the sha512hash program and passes the CL arguments
    }
    else{
        //if this is the parent process, then it will wait for the child process to finish before moving on
        wait(NULL);
    }

    //Starting the second child
    pid_t child2_pid = fork();

    if (child2_pid < 0){
        printf("child2 forking failed\n");
        return -1;
    }
    else if (child2_pid == 0){
        int pid = getpid();
        int ppid = getppid();

        printf("Child2: pid %d, ppid %d\n", pid, ppid);
        fflush(stdout);//waiting to print before moving on

        pthread_t thread;//creating the thread
        struct Date* difference;

        //starting the thread to calculate the difference in the dates
        pthread_create(&thread, NULL, &calculateDateDifference, (void *)&dateSt);

        //waits for the thread to complete
        pthread_join(thread, (void **) &difference);

        printf("\tTime until %s is %d days, %d months and %d years\n",date, difference->day, difference->month, difference->year);
    }
    else{
        //if this is the parent process, then it will wait for the child process to finish before moving on
        wait(NULL);
    }

    return 0;
}
