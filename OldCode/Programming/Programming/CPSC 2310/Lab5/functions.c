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

bool checkInvalidDate(node_t *node){

    //if any of these months, then check the days
    if(strcmp(node->bDay.month, "January") == 0 || 
    strcmp(node->bDay.month, "March") == 0|| 
    strcmp(node->bDay.month, "May") == 0|| 
    strcmp(node->bDay.month, "July") == 0 ||
    strcmp(node->bDay.month, "August") == 0|| 
    strcmp(node->bDay.month, "October") == 0||
    strcmp(node->bDay.month, "December") == 0){

        //this is where we check for the correct days
        if(node->bDay.day <= 31 && node->bDay.day > 0){
            return true;
        }
        else{
            return false;
        }
    }

    //if any of these months, then check the days
    else if(strcmp(node->bDay.month, "April") == 0|| 
    strcmp(node->bDay.month, "June") == 0|| 
    strcmp(node->bDay.month, "September") == 0|| 
    strcmp(node->bDay.month, "November") == 0){

        //this is where we check for the correct days
        if(node->bDay.day <= 30 && node->bDay.day > 0){
            return true;
        }
        else{
            return false;
        }
    }

    //everything else should be feburary
    else{

        //call to helper function to check for leap year
        if(checkForLeap(node)){
            if(node->bDay.day <= 29 && node->bDay.day > 0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(node->bDay.day <= 28 && node->bDay.day > 0){
                return true;
            }
            else{
                return false;
            }
        }
        
    }

}

bool checkForLeap(node_t *node){ 
    //this would mean a leap year
    if (node->bDay.year % 400 == 0) {
      return true;
   }
   //this would not be a leap year
   else if (node->bDay.year % 100 == 0) {
      return false;
   }
    //this would mean a leap year
   else if (node->bDay.year % 4 == 0) {
      return true;
   }
   //everything else would be a leap year
   else {
      return false;
   }
}

node_t* createList(FILE* input,node_t** head){

    //while not at the end of the file, keep looping
    while(!(feof(input))){

        //this will create the node
        node_t *node = readNodeInfo(input);

        //this calls the function to check if there are any dupicaltes
        //It will also check for valid days to months
        if(!dup(&node, head) && checkInvalidDate(node)){

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

void sortList(node_t **head, fp comp){
    node_t* h = *head;
    //used to go through the while loop
    bool check = true;
    while(check == true){
        check = false;
        h = *head;
        while(h->next != NULL){
            //will loop until we are at the null
            if(comp(h, h->next) > 0){
                swap(h, h->next, head);
                check = true;
            }
            //this line is extremely important to stop the loop
            if(h->next != NULL){
                h = h->next;
            }
        }  
    }
}

void swap(node_t *a, node_t *b, node_t **head){
    //this will be the edge case
    if(a == *head){
        node_t *temp = *head;
        *head = b;
        temp->next = (*head)->next;
        (*head)->next = temp;
        
    }
    //this is where the main swapping occurs
    else{
        node_t *prev;
        prev = *head;
        //this will iterate prev until back to a each time
        while(prev->next != a){
            prev = prev->next;
        }
        node_t* b_next = prev->next->next->next;
        prev->next = b;
        prev->next->next = a;
        prev->next->next->next = b_next;
    }
    
}

int compare_by_lastname(node_t *a, node_t *b){
    //strcmp returns a value either 0, <0, or >0
    return strcmp(a->lastName, b->lastName);
}

int compare_by_firstname(node_t *a, node_t *b){
    return strcmp(a->firstName, b->firstName);
}