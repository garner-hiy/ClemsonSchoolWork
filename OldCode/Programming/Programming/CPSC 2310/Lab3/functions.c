/**************************
*AJ Garner*
*CPSC 2310 Spring 23 *
*UserName: adgarne*
*Instructor: Dr. Yvon Feaster *
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

        //this calls the function to check if there are any dupicaltes
        if(!dup(&node, head)){

            //if there are no dups, then it will add to the list
            add(&node, head);
        }

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

