// Names in Group: AJ Gardner, Mitchell L. Pohar
// Date: 16 February 2024
// Class: CPSC 3220
// Assignment: HW2

// To Compile: gcc -Wall sched.c -o sched

// To Run: ./sched -prio < [input] > [output]
//          or
//         ./sched -custom < [input] > [output]

// To create a compressed archived file:
// tar -cvzf hw2.tar.gz sched.c makefile

// To extract a compressed archived file:
// tar -xvzf hw2.tar.gz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h> // Include for isatty

// Define task structure
struct task{
    int
    task_id, // Alphabetic identifier
    arrival_time,
    service_time,
    remaining_time,
    completion_time,
    response_time,
    wait_time,
    priority;
    struct task *next; // Pointer to next task in the list
} *readyQueue, *arrivalQueue, *finishedQueue, *CPU;

typedef struct task *node;

// Function to simulate priority-based scheduling
void simulatePriority();
// Function to simulate custom (preemptive) scheduling
void simulateCustom();
// Function to print simulation status at each time unit
void printSim(int time);
// Function to print final task summary and statistics
void printResult();

// Queue operations for the arrival queue
void arrivalEnqueue(node newNode);
node arrivalDequeue();

// Queue operations for the ready queue
void readyEnqueue(node newNode);
node readyDequeue();

// Enqueue operation for the finished queue
void finishedEnqueue(node newNode);

// Utility function to check if a queue is empty
bool isEmpty(node currentNode);
// Removes a task from the ready queue
void removeFromReadyQueue(node highestPriority);
// Swaps two integer values (used in sorting)
void swapTasks(int *task1, int *task2);


int main(int argc, char * argv[]) {

    // Check for file redirection in input and output
    if (isatty(STDIN_FILENO) || isatty(STDOUT_FILENO)) {
        fprintf(stderr, "Error: This program requires file redirection for both input and output.\n");
        fprintf(stderr, "Usage: %s -prio | -custom < inputFile > outputFile\n", argv[0]);
        return 1;
    }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s -prio | -custom < inputFile > outputFile\n", argv[0]);
        return 1;
    }
    
    char *policy = argv[1];

    int temp = 0;
    int type = 0;
    int counter = 'Y';

    node newNode;
    //First it reads in all of the numbers of the file
    while (scanf("%d", &temp) != EOF) {

        //The type variable identifies which variable it should be desined to
        //type = 0 identifies the arrival time and type = 1 is the service time
        if(type == 0) {
            //It then creates a new node with its task id and arrival time and changes the type to service time
            newNode = (node)malloc(sizeof(struct task));
            newNode->task_id = counter;
            if (counter > 'Z') {
                counter = 'A';
                newNode->task_id = counter;
            }
            newNode->arrival_time = temp;
            type++;
            counter++;
        }
        else if (type == 1) {

            //It then changes the type back to arrival time and then sets the service time and remaining time
            newNode->service_time = temp;
            newNode->remaining_time = temp;

            //Uninitialized values get temporarily initialized in the new task
            newNode->completion_time = 0;
            newNode->response_time = 0;
            newNode->wait_time = 0;
            newNode->next = NULL;

            type++;
        }
        else{
            type = 0;
            newNode->priority = temp;
            //The node is then allocated to the allocated list
            arrivalEnqueue(newNode);
        }
    }

    // Select scheduling policy based on command-line argument
    if (strcmp(policy, "-prio") == 0) simulatePriority();
    else if (strcmp(policy, "-custom") == 0) simulateCustom();
    else {
        fprintf(stdout, "Invalid policy. Use -prio or -custom.\n");
        return 1;
    }

    //Then the finished linked list is freed to deallocate all memory
    node tempNode = finishedQueue;
    while (tempNode != NULL) {
        finishedQueue = finishedQueue->next;
        free(tempNode);
        tempNode = finishedQueue;
    }
    return 0;
}


void simulatePriority(){
    //First it prints the header
    printf("Priority scheduling results\n\n");
    printf("time\tcpu  priority  ready queue (tid/rst)\n");
    printf("---------------------------------------------\n");

    int currentTime = 0;
    bool cpu_idle = true; // Flag to indicate whether CPU is idle

    // While there are tasks in arrival queue or CPU is not empty
    while (!isEmpty(arrivalQueue) || CPU != NULL || !isEmpty(readyQueue)) {
        // Check for task arrivals
        while (!isEmpty(arrivalQueue) && arrivalQueue->arrival_time <= currentTime) {
            node new_task = arrivalDequeue();
            readyEnqueue(new_task);
        }

        // Find the highest priority task with shortest service time
        node highest_priority_task = NULL;
        node temp = readyQueue;
        while (temp != NULL) {
            if (highest_priority_task == NULL ||
                temp->priority < highest_priority_task->priority ||
                (temp->priority == highest_priority_task->priority && temp->service_time < highest_priority_task->service_time)) {
                highest_priority_task = temp;
            }
            temp = temp->next;
        }

        // If CPU is empty and there's a task in ready queue, run the task
        if (CPU == NULL && highest_priority_task != NULL) {
            CPU = highest_priority_task;
            removeFromReadyQueue(highest_priority_task);
            // CPU is not idle
            cpu_idle = false; 
        }

        // Increment wait_time for nodes in readyQueue if CPU is running
        if (!cpu_idle) {
            temp = readyQueue;
            while (temp != NULL) {
                temp->wait_time++;
                temp = temp->next;
            }
        }

        // Print simulation for current time unit
        printSim(currentTime);

        // If CPU is running, decrement its remaining service time
        if (CPU != NULL) {
            CPU->remaining_time--;

            // If CPU finished its service, move it to finished queue
            if (CPU->remaining_time == 0) {
                CPU->completion_time = currentTime + 1;
                CPU->response_time = (CPU->service_time + CPU->wait_time);
                finishedEnqueue(CPU);
                CPU = NULL;
                cpu_idle = true; // CPU becomes idle after task completion
            }
        }

        currentTime++; // Increment time
    }

    // Print task summary
    printResult();
}
void simulateCustom(){

    // First, print the header
    printf("Custom (preemptive) scheduling results\n\n");
    printf("time\tcpu  priority  ready queue (tid/rst)\n");
    printf("---------------------------------------------\n");

    int currentTime = 0;
    // Time quantum for the custom scheduling algorithm
    int time_quantum = 1; 
    bool cpu_idle = true;

    // While there are tasks in the arrival queue or CPU is not empty
    while (!isEmpty(arrivalQueue) || CPU != NULL || !isEmpty(readyQueue)) {
        // Check for task arrivals
        while (!isEmpty(arrivalQueue) && arrivalQueue->arrival_time <= currentTime) {
            node new_task = arrivalDequeue();
            readyEnqueue(new_task);
        }

        // Find the highest priority task with shortest service time
        node highest_priority_task = NULL;
        node temp = readyQueue;
        while (temp != NULL) {
            if (highest_priority_task == NULL ||
                temp->priority < highest_priority_task->priority ||
                (temp->priority == highest_priority_task->priority && temp->service_time < highest_priority_task->service_time)) {
                highest_priority_task = temp;
            }
            temp = temp->next;
        }

        // If CPU is empty and there's a task in ready queue, run the task
        if (CPU == NULL && highest_priority_task != NULL) {
            CPU = highest_priority_task;
            removeFromReadyQueue(highest_priority_task);
            cpu_idle = false;
        }

        // Increment wait_time for nodes in readyQueue if CPU is running
        if (!cpu_idle) {
            node temp = readyQueue;
            while (temp != NULL) {
                temp->wait_time++;
                temp = temp->next;
            }
        }

        // Print simulation for current time unit
        printSim(currentTime);

        // If CPU is running, decrement its remaining service time
        if (CPU != NULL) {
            CPU->remaining_time--;

            // If CPU finished its time quantum or service, move it back to ready queue
            if (CPU->remaining_time != 0 && currentTime % time_quantum == 0) {
                // Lower the priority
                CPU->priority++; 
                readyEnqueue(CPU);
                CPU = NULL;
                cpu_idle = true;
            }
            // If CPU finished its service, move it to finished queue
            else if (CPU->remaining_time == 0) {
                CPU->completion_time = currentTime + 1;
                CPU->response_time = (CPU->service_time + CPU->wait_time);
                CPU->priority = (CPU->priority - CPU->service_time +1);
                finishedEnqueue(CPU);
                CPU = NULL;
                // CPU becomes idle after task completion
                cpu_idle = true; 
            }
        }

        currentTime++;
    }

    printResult();
}

void arrivalEnqueue(node newNode){
    //First it sets a temporary node to hold the arriving queue
    node tempNode = arrivalQueue;
    
    //Then it checks if the arriving queue is empty and sets the new node to arriving
    if(isEmpty(arrivalQueue)) arrivalQueue = newNode;
    else {
        //If the queue has elements, it then places the element at the end of the linked list
        while (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}
node arrivalDequeue(){
    //First it creates a return node and a temporary head for the arriving queue
    node returnNode;
    node tempHead = arrivalQueue;

    //The return node is then set to the head
    returnNode = tempHead;

    //It then checks if there is another element, and if there is, it sets it as the new head
    //If not, it sets it to null
    if(tempHead->next != NULL) arrivalQueue = tempHead->next;
    else arrivalQueue = NULL;

    //It then returns the returnNode
    returnNode->next = NULL;
    return returnNode;
}

void readyEnqueue(node newNode){
    //First it sets a temporary node to hold the ready queue
    node tempNode = readyQueue;

    //Then it checks if the ready queue is empty and sets the new node to ready
    if(isEmpty(readyQueue)) readyQueue = newNode;
    else {
        //If the queue has elements, it then places the element at the end of the linked list
        while (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}
node readyDequeue(){
    //First it creates a return node and a temporary head for the ready queue
    node returnNode;
    node tempHead = readyQueue;

    //The return node is then set to the head
    returnNode = tempHead;

    //It then checks if there is another element, and if there is, it sets it as the new head
    //If not, it sets it to null
    if(tempHead->next != NULL) readyQueue = tempHead->next;
    else readyQueue = NULL;
    
    //It then returns the returnNode
    returnNode->next = NULL;
    return returnNode;
}

void finishedEnqueue(node newNode){
    //First it sets a temporary node to hold the finished queue
    node tempNode = finishedQueue;
    
    //Then it checks if the finished queue is empty and sets the new node to arriving
    if(isEmpty(finishedQueue)) finishedQueue = newNode;
    else {
        //If the queue has elements, it then places the element at the end of the linked list
        while (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

bool isEmpty(node currentNode){
    if(currentNode == NULL) return true;
    return false;
}

void removeFromReadyQueue(node highestPriority) {
    // If the highestPriority node is the head of the readyQueue
    if (readyQueue == highestPriority) {
        readyQueue = readyQueue->next;
        highestPriority->next = NULL;
        return;
    }

    // If the highestPriority node is not the head, find and remove it
    node temp = readyQueue;
    while (temp->next != NULL) {
        if (temp->next == highestPriority) {
            temp->next = highestPriority->next;
            highestPriority->next = NULL; 
            return;
        }
        temp = temp->next;
    }
}
void swapTasks(int *task1, int *task2){
    int temp = *task1;
    *task1 = *task2;
    *task2 = temp;
}

void printSim(int time){
    //First it prints out the time using a right justification and tabs
    printf("%3d\t", time);

    // Print CPU status
    if (CPU != NULL) printf("%c%d\t", CPU->task_id, CPU->remaining_time);
    else printf("  \t");

    // Print priority of the task on CPU
    if (CPU != NULL) printf("%d\t", CPU->priority);
    else printf("\t");

    // Print ready queue status
    if (isEmpty(readyQueue)) printf("--");
    else {
        node tempNode = readyQueue;
        printf("%c%d  %d  ", readyQueue->task_id, readyQueue->remaining_time, readyQueue->priority);
        while (tempNode->next != NULL) {
            tempNode = tempNode->next;
            printf("\t%c%d  %d  ", tempNode->task_id, tempNode->remaining_time, tempNode->priority);
        }
    }

    printf("\n");
}
void printResult(){
    //First it prints the header
    printf("\n");
    printf("\t\tarrival\tservice\tcompletion response wait\n");
    printf("tid\tprio\ttime\ttime\ttime\t   time\t    time\n");
    printf("--------------------------------------------------------\n");
    
    // Find the smallest task_id to start printing from
    int min_tid = 'A';
    int items = 0;
    node tempHead = finishedQueue;
    while (tempHead != NULL) {
        if (tempHead->task_id < min_tid) {
            min_tid = tempHead->task_id;
        }
        tempHead = tempHead->next;
    }

    // Print the nodes in ascending order of task_id
    while (min_tid <= 'Z') {
        tempHead = finishedQueue;
        while (tempHead != NULL) {
            // Found and printed the node, move to the next task_id
            if (tempHead->task_id == min_tid) {
                printf("%2c\t%3d\t%3d\t%3d", tempHead->task_id, tempHead->priority, tempHead->arrival_time, tempHead->service_time);
                printf("\t %3d\t  %3d\t   %3d\n", tempHead->completion_time, tempHead->response_time, tempHead->wait_time);
                items++;
                break; 
            }
            tempHead = tempHead->next;
        }
        min_tid++;
    }
    
    //Then it prints the header for the final table
    printf("\nservice\twait\n time\ttime\n------- ----\n");
    
    //initializing the arrays for service times and wait times
    int service[items];
    int wait[items];
    tempHead = finishedQueue;
    for(int i = 0; i < items; i++) {
        service[i] = tempHead->service_time;
        wait[i] = tempHead->wait_time;
        tempHead = tempHead->next;
    }

    //First bubble sort that sorts the service times in order
    //It also places the wait times to their corresponding service
    int swapCounter;
    int swapped;
    int i;
    for(swapCounter = 0; swapCounter < items - 1; swapCounter++) {
        swapped = 0;
        for(i = 0; i < items - swapCounter - 1; i++) {
            if(service[i] > service[i + 1]){
                swapTasks(&service[i], &service[i + 1]);
                swapTasks(&wait[i], &wait[i + 1]);
                swapped = 1;
            }
        }
        if(swapped == 0) break;
    }
    //Second bubble sort that only sorts the elements in the wait time array
    //the condition for the swap is if there are duplicates in the service time array
    for(swapCounter = 0; swapCounter < items - 1; swapCounter++) {
        swapped = 0;
        for(i = 0; i < items - swapCounter - 1; i++) {
            if(service[i] == service[i + 1]){
                if(wait[i] > wait[i + 1]) swapTasks(&wait[i], &wait[i + 1]);
            }
        }
        if(swapped == 0) break;
    }
    //loop that prints out each of the elements from the 
    //service time array and wait time array
    for(int counter = 0; counter < items; counter++){
        printf("%3d     %3d\n", service[counter], wait[counter]);
    }
}