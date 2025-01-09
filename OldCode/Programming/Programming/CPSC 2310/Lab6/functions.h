/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
*email: adgarne@clemson.edu*
*************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//this struct is for the birthday information
typedef struct Birthday{
    char month[10];
    int day;    
    int year;
}birthday_t;

//this struct is for all the rest of the information
typedef struct Node{
    char firstName[50];
    char lastName[50];
    char major[50];
    char classStanding[50];
    birthday_t bDay;
    struct Node *next;
}node_t;

//this struct will store the data for birthdays
typedef struct List_stats{
    node_t *oldest;
    node_t *youngest;
    int birthMonths[11];
}list_stats_t;

//implement these:
void add(node_t **node, node_t **head);
node_t* readNodeInfo(FILE* input);
node_t* createList(FILE*, node_t**);
void printList(FILE*, node_t*);
void printBorder(FILE*);
void deleteList(node_t** );

//added a helper function to check for duplicates
bool dup(node_t **node, node_t **head);



list_stats_t getListStats(node_t *head);

void printStats(FILE* output, list_stats_t *pt);

//helper functions
bool checkB(node_t *a, node_t *b);
int compareMonths(char a[]);

#endif