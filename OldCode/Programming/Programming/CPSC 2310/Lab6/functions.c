/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
*email: adgarne@clemson.edu*
*************************/
#include "functions.h"

//This function will check for duplicates
bool dup(node_t **node, node_t **head){

    //iterator node
    node_t *itr = *head;

    //start the returning variable with false
    bool check = false;
    while(itr != NULL){

        //this if is used to compare all the elements of the nodes
        if(strcmp(itr->lastName, (*node)->lastName) == 0 && 
        strcmp(itr->firstName, (*node)->firstName) == 0
        && strcmp(itr->bDay.month, (*node)->bDay.month) == 0 && 
        itr->bDay.day == (*node)->bDay.day && 
        itr->bDay.year == (*node)->bDay.year 
        && strcmp(itr->major, (*node)->major) == 0 && 
        strcmp(itr->classStanding, (*node)->classStanding) == 0){

            //this changes the variable to true to be returned
            check = true;
        }

        //move to the next node
        itr = itr->next;
    }
    return check;
}

void add(node_t **node, node_t **head){

    //iterator node
    node_t *itr = *head;

    //if the list is empty, then make the head node the current node
    if(*head == NULL){
        *head = *node;
    }
    
    //else it will iterate through and add the node at the end of the list
    else{
        while(itr->next != NULL){
            itr = itr->next;
        }
        itr->next = *node;
    }
}

node_t* readNodeInfo(FILE* input){
    
    //allocate memory for the node being created
    node_t *node = (node_t *) malloc(sizeof(node_t));

    //temps needed to convert string to integer
    char tempDay[3];
    char tempYear[5];

    //scanset converation 
    //these fscanf statements will read from input till a comma
    fscanf(input, "%[^,]%*c", node->lastName);
    fscanf(input, "%[^,]%*c", node->firstName);
    fscanf(input, "%[^,]%*c", node->bDay.month);
    fscanf(input, "%[^,]%*c", tempDay);
    fscanf(input, "%[^,]%*c", tempYear);

    //these two lines convert and store the data as integers
    node->bDay.day = atoi(tempDay);
    node->bDay.year = atoi(tempYear);

    fscanf(input, "%[^,]%*c", node->major);
    fscanf(input, "%[^\n]%*c", node->classStanding);


    return node;
}

node_t* createList(FILE* input,node_t** head){

    //while not at the end of the file, keep looping
    while(!(feof(input))){

        //this will create the node
        node_t *node = readNodeInfo(input);
        add(&node, head);

    }

    //returns the pointer to the start of the list
    return *head;
}
void printList(FILE* output, node_t* node){
    
    //if the list is empty, then print that
    if(node == NULL){
        printf("LIST IS EMPTY\n");
    }

    //else it will print the proper format and use a while loop to print 
    //the information from the nodes and iterators to the next node
    else{
        printBorder(output);
        fprintf(output,"\n");
        fprintf(output,"List Info:\n");

        //iterator node
        node_t *itr = node;

        while(itr != NULL){
            fprintf(output,"Name:\t%s %s\n", itr->firstName, itr->lastName);
            fprintf(output,"Date of Birth:\t%s %d, "
            "%d\n", itr->bDay.month, itr->bDay.day, itr->bDay.year);
            fprintf(output,"Major:\t%s\n", itr->major);
            fprintf(output,"Year:\t%s\n\n", itr->classStanding);
            itr = itr->next;
        }
        printBorder(output);
    }
}

//this will print the border needed for formatting
void printBorder(FILE* out)
{
    int i = 0;
    for(i = 0; i < 80; i++)
        fprintf(out,"*");
    
    fprintf(out, "\n");
}

//This will use two iterator nodes and itr to the next node and free
//the memory from the previous using prev node. Next it will make prev 
//the same node as the current itr.
void deleteList(node_t** node){

    //the two iterator nodes
    node_t *itr = *node;
    node_t *prev = *node;

    while(itr->next != NULL){
        itr = itr->next;
        free(prev);
        prev = itr;
    }

    //need to delete the last of the memory
    free(itr);
}

list_stats_t getListStats(node_t *head){
    //iterator node
    node_t *h = head;
    
    //declare the struct to store everything
    list_stats_t stuff;

    //need to initialize the array to all 0s
    for(int i = 0; i < 12; i++){
        stuff.birthMonths[i] = 0;
    }

    //setting the node pointers to the head
    stuff.oldest = head;
    stuff.youngest = head;

    //this is the loop that will check for both extremes
    while(h != NULL){
        //if h is younger, then update
        if(checkB(h, stuff.youngest)){
            stuff.youngest = h;
        }
        //if h is older, then update
        if(!checkB(h, stuff.oldest)){
            stuff.oldest = h;
        }
        //move to the next node to compare
        h = h->next;
    }

    h = head;

    //this while loop will count the months and store it into the array
    while(h != NULL){
        if(strcmp(h->bDay.month, "January") == 0){
            stuff.birthMonths[0] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "February") == 0){
            stuff.birthMonths[1] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "March") == 0){
            stuff.birthMonths[2] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "April") == 0){
            stuff.birthMonths[3] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "May") == 0){
            stuff.birthMonths[4] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "June") == 0){
            stuff.birthMonths[5] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "July") == 0){
            stuff.birthMonths[6] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "August") == 0){
            stuff.birthMonths[7] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "September") == 0){
            stuff.birthMonths[8] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "October") == 0){
            stuff.birthMonths[9] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "November") == 0){
            stuff.birthMonths[10] += 1;
            h = h->next;
        }
        else if(strcmp(h->bDay.month, "December") == 0){
            stuff.birthMonths[11] += 1;
            h = h->next;
        }
    }
    return stuff;
}

//it will return true if a is greater than or equal to b. Or else return false
//returning true will mean a is younger 
//returning false will mean a is older
bool checkB(node_t *a, node_t *b){
    if(a->bDay.year > b->bDay.year){
        return true;    
    }
    else if(a->bDay.year == b->bDay.year){
        if(compareMonths(a->bDay.month) > compareMonths(b->bDay.month)){
            return true;
        }
        else if(compareMonths(a->bDay.month) == compareMonths(b->bDay.month)){
            if(a->bDay.day > b->bDay.day){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}


//this will return a compareable value for the months
int compareMonths(char a[]){
    if(strcmp(a, "January") == 0)
    return 0;
    if(strcmp(a, "February") == 0)
    return 1;
    if(strcmp(a, "March") == 0)
    return 2;
    if(strcmp(a, "April") == 0)
    return 3;
    if(strcmp(a, "May") == 0)
    return 4;
    if(strcmp(a, "June") == 0)
    return 5;
    if(strcmp(a, "July") == 0)
    return 6;
    if(strcmp(a, "August") == 0)
    return 7;
    if(strcmp(a, "September") == 0)
    return 8;
    if(strcmp(a, "October") == 0)
    return 9;
    if(strcmp(a, "November") == 0)
    return 10;
    if(strcmp(a, "December") == 0)
    return 11;
    else
    return -1;
}


//This will print the stats out and is setup to format correctly
void printStats(FILE* output, list_stats_t *pt){
    
    printBorder(output);

    fprintf(output,"List Statistics:\n");
    fprintf(output,"----------Oldest Person----------\n");
    fprintf(output,"Name:\t%s %s\n", pt->oldest->firstName, pt->oldest->lastName);
    fprintf(output,"Date of Birth:\t%s %d, "
    "%d\n", pt->oldest->bDay.month, pt->oldest->bDay.day, pt->oldest->bDay.year);
    fprintf(output,"Major:\t%s\n", pt->oldest->major);
    fprintf(output,"Year:\t%s\n\n", pt->oldest->classStanding);
    
    fprintf(output,"----------Youngest Person----------\n");
    fprintf(output,"Name:\t%s %s\n", pt->youngest->firstName, pt->youngest->lastName);
    fprintf(output,"Date of Birth:\t%s %d, "
    "%d\n", pt->youngest->bDay.month, pt->youngest->bDay.day, pt->youngest->bDay.year);
    fprintf(output,"Major:\t%s\n", pt->youngest->major);
    fprintf(output,"Year:\t%s\n\n", pt->youngest->classStanding);

    fprintf(output,"----------Birthday Counts----------\n");
    fprintf(output,"January: %d\n", pt->birthMonths[0]);
    fprintf(output,"February: %d\n", pt->birthMonths[1]);
    fprintf(output,"March: %d\n", pt->birthMonths[2]);
    fprintf(output,"April: %d\n", pt->birthMonths[3]);
    fprintf(output,"May: %d\n", pt->birthMonths[4]);
    fprintf(output,"June: %d\n", pt->birthMonths[5]);
    fprintf(output,"July: %d\n", pt->birthMonths[6]);
    fprintf(output,"August: %d\n", pt->birthMonths[7]);
    fprintf(output,"September: %d\n", pt->birthMonths[8]);
    fprintf(output,"October: %d\n", pt->birthMonths[9]);
    fprintf(output,"November: %d\n", pt->birthMonths[10]);
    fprintf(output,"December: %d\n", pt->birthMonths[11]);
    printBorder(output);
    
}