/*
Chapter 11 - structures
*/

#include <stdio.h>
#include <string.h>
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

void GetData (StudentInfo student[], int size);
void PrintData (StudentInfo student[], int size);
//GradeInfo GetAverage (StudentInfo student);//calculate average
double GetAverage (GradeInfo grades);

int main (void){

    //StudentInfo student1;
    //StudentInfo student2;
    int numStudents;

    printf("How many students to enter: \n");
    scanf("%d", &numStudents);

    StudentInfo student[numStudents];//an array of sturcts

    GetData(student, numStudents);
    PrintData(student, numStudents); 
    /*using the GradeInfo return function
    for(int i = 0; i < numStudents; ++i){
        student[i].grades = GetAverage(student[i]);
    }
    */
    for(int i = 0; i < numStudents; ++i){
        student[i].grades.average = GetAverage(student[i].grades);
    }

    /*Examples:
    student2 = student1;//will copy the whole struct
    student2.age = student1.age;//can do this with single integers or charaters
    strcpy(student2.firstName, student1.firstName);//to copy a string over
    printf("First letter of firstName: %c", student2.firstName[0]);*/

    return 0;
}

void GetData (StudentInfo student[], int size){

    for(int i = 0; i < size; ++i){
        printf("Enter a first name: \n");
        scanf("%s", student[i].firstName);

        printf("Enter a last name: \n");
        scanf("%s", student[i].lastName);

        printf("Enter an age: \n");
        scanf("%d", &student[i].age);

        printf("Enter a major: \n");
        fgets(student[i].major, 50, stdin);

        printf("Enter a midterm 1: \n");
        scanf("%d", &student[i].grades.midterm1);

        printf("Enter a midterm 2: \n");
        scanf("%d", &student[i].grades.midterm2);

        printf("Enter a midterm 3: \n");
        scanf("%d", &student[i].grades.midterm3);

        printf("Enter notes: \n");
        fgets(student[i].notes, 200, stdin);
    }  
}

void PrintData (StudentInfo student[], int size){

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
/*
GradeInfo GetAverage(StudentInfo student){


    student.grades.average = (student.grades.midterm1 + student.grades.midterm2 + student.grades.midterm3) / 3.0;
    

    return student.grades;
}
*/
double GetAverage(GradeInfo grades){


    grades.average = (grades.midterm1 + grades.midterm2 + grades.midterm3) / 3.0;
    return grades.average;
}
