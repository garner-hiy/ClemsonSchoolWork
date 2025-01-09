#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct task {
    int task_id;
    int arrival_time;
    int service_time;
    int remaining_time;
    int priority;
    int completion_time;
    int response_time;
    int wait_time;
    struct task *next;
};

struct task *head = NULL;
int global_time = 0, task_counter = 0;
char current_task_id = 'Y';

// Function Prototypes
void add_task(int arrival, int service, int priority);
void simulate_priority_based(FILE *outputFile);
void simulate_custom(FILE *outputFile);
void print_simulation_trace(FILE *outputFile, char *scheduling_type);
void print_task_summary(FILE *outputFile);
struct task *select_next_task_priority_based();
struct task *select_next_task_custom();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s -prio | -custom\n", argv[0]);
        return 1;
    }
    
    char *policy = argv[1];
    int arrival, service, priority;
    
    // Read tasks from stdin
    while (scanf("%d %d %d", &arrival, &service, &priority) != EOF) {
        add_task(arrival, service, priority);
    }
    
    // Redirect output to a file via command line redirection
    FILE *outputFile = stdout;
    
    // Select scheduling policy based on command-line argument
    if (strcmp(policy, "-prio") == 0) {
        simulate_priority_based(outputFile);
    } else if (strcmp(policy, "-custom") == 0) {
        simulate_custom(outputFile);
    } else {
        printf("Invalid policy. Use -prio or -custom.\n");
        return 1;
    }
    
    // Print simulation trace and task summary
    print_simulation_trace(outputFile, policy);
    print_task_summary(outputFile);
    
    return 0;
}

void add_task(int arrival, int service, int priority) {
    struct task *new_task = (struct task *)malloc(sizeof(struct task));
    new_task->task_id = 'A' + (task_counter++ % 26);
    new_task->arrival_time = arrival;
    new_task->service_time = service;
    new_task->remaining_time = service;
    new_task->priority = priority;
    new_task->completion_time = 0;
    new_task->response_time = -1; // -1 indicates the response time has not been set
    new_task->wait_time = 0;
    new_task->next = NULL;

    if (head == NULL || head->arrival_time > arrival) {
        new_task->next = head;
        head = new_task;
    } else {
        struct task *current = head;
        while (current->next != NULL && current->next->arrival_time <= arrival) {
            current = current->next;
        }
        new_task->next = current->next;
        current->next = new_task;
    }
}

void simulate_priority_based(FILE *outputFile) {
    struct task *current_task = NULL;
    int current_time = 0;

    while (head != NULL) {
        if (current_task == NULL || current_task->remaining_time == 0) {
            current_task = select_next_task_priority_based();
            if (current_task != NULL) {
                if (current_task->response_time == -1) {
                    current_task->response_time = current_time - current_task->arrival_time;
                }
                current_task->remaining_time--;
                if (current_task->remaining_time == 0) {
                    current_task->completion_time = current_time + 1;
                }
            }
        } else {
            current_task->remaining_time--;
            if (current_task->remaining_time == 0) {
                current_task->completion_time = current_time + 1;
            }
        }
        current_time++;
    }
}

void simulate_custom(FILE *outputFile) {
    struct task *current_task = NULL;
    int current_time = 0;

    while (head != NULL) {
        struct task *new_task = select_next_task_custom();
        if (new_task != current_task) {
            if (current_task != NULL && current_task->remaining_time > 0) {
                // Return the preempted task back to the queue
                add_task(current_time, current_task->remaining_time, current_task->priority + 1);
            }
            current_task = new_task;
            if (current_task->response_time == -1) {
                current_task->response_time = current_time - current_task->arrival_time;
            }
        }
        if (current_task != NULL) {
            current_task->remaining_time--;
            if (current_task->remaining_time == 0) {
                current_task->completion_time = current_time + 1;
            }
        }
        current_time++;
    }
}

void print_simulation_trace(FILE *outputFile, char *scheduling_type) {
    // Placeholder for printing the simulation trace
    fprintf(outputFile, "Simulation Trace:\n");
}

void print_task_summary(FILE *outputFile) {
    // Placeholder for printing the task summary
    fprintf(outputFile, "Task Summary:\n");
}

struct task* select_next_task_priority_based() {
    struct task *current = head, *selected_task = NULL;
    while (current != NULL) {
        if ((selected_task == NULL || current->priority < selected_task->priority) && current->arrival_time <= global_time) {
            selected_task = current;
        }
        current = current->next;
    }
    return selected_task;
}

struct task* select_next_task_custom() {
    struct task *current = head, *selected_task = NULL;
    while (current != NULL) {
        if (current->arrival_time <= global_time) {
            if (selected_task == NULL || 
               current->priority < selected_task->priority || 
               (current->priority == selected_task->priority && current->remaining_time < selected_task->remaining_time)) {
                selected_task = current;
            }
        }
        current = current->next;
    }
    return selected_task;
}
