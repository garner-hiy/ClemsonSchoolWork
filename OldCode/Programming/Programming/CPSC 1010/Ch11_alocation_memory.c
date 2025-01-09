#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct GradeStruct_struct{
    int midterm1;
    int midterm2;
    int midterm3;
    double average;
}GradeInfo;

typedef struct StudentStruct_struct{
    char firstName[20];
    char lastName[20];
    int age;
    char major[50];
    char notes[200];
    GradeInfo grades;
}StudentInfo;

void GetData (StudentInfo* student, int size);
void PrintData (StudentInfo* student, int size);
double GetAverage (GradeInfo grades);

int main (void){

    int numStudents;

    printf("How many students to enter: \n");
    scanf("%d", &numStudents);

    StudentInfo* student = NULL;//pointer to a struct that will have dynamic memory
    student = (StudentInfo*)(malloc(numStudents * sizeof(StudentInfo)));

    GetData(student, numStudents);
     
    for(int i = 0; i < numStudents; ++i){
        student[i].grades.average = GetAverage(student[i].grades);
    }

    PrintData(student, numStudents);

    return 0;
}

void GetData (StudentInfo* student, int size){

    for(int i = 0; i < size; ++i){
        printf("Enter a first name: \n");
        scanf("%s", student[i].firstName);

        printf("Enter a last name: \n");
        scanf("%s", student[i].lastName);

        printf("Enter an age: \n");
        scanf("%d", &student[i].age);

        getchar();//this grabs the newline and holds it away from the buffer

        printf("Enter a major: \n");
        fgets(student[i].major, 50, stdin);

        printf("Enter a midterm 1: \n");
        scanf("%d", &student[i].grades.midterm1);

        printf("Enter a midterm 2: \n");
        scanf("%d", &student[i].grades.midterm2);

        printf("Enter a midterm 3: \n");
        scanf("%d", &student[i].grades.midterm3);

        getchar();

        printf("Enter notes: \n");
        fgets(student[i].notes, 200, stdin);
    }  
}

void PrintData (StudentInfo* student, int size){

    for(int i = 0; i < size; ++i){
        printf("First name: %s\n", student[i].firstName);

        printf("Last name: %s\n",student[i].lastName);

        printf("Age: %d\n", student[i].age);

        printf("Major: %s\n", student[i].major);

        printf("Midterm 1: %d\n", student[i].grades.midterm1);

        printf("Midterm 2: %d\n", student[i].grades.midterm2);

        printf("Midterm 3: %d\n", student[i].grades.midterm3);

        printf("Notes: %s\n", student[i].notes);
    }  
}
double GetAverage(GradeInfo grades){


    grades.average = (grades.midterm1 + grades.midterm2 + grades.midterm3) / 3.0;
    return grades.average;
}