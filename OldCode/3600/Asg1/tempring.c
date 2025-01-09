/*
Name: AJ Garner
Class: CPSC 3600
Purpose:
    This program will take in a ip addresses, port numbers, and a txt file
    that will be passed around 3 computers. They will all act as a server
    and a client.

Compile: 
    run "make"
    -With all files in the same directory.

When done, run "make clean"

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include "Practical.h"

typedef struct {
    char *file; //holds what was in the file
    char *localip; //stores the local ip address
    char *distantip; //stores the destination ip address
    char *previp; //stores the ip address from the previous machine
    char *port; //stores the port number
} ThreadArgs;


void *server_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    ThreadArgs *thread_out = malloc(sizeof(ThreadArgs));

    int servSock = SetupTCPServerSocket(thread_args->port);
    if (servSock < 0)
        DieWithUserMessage("SetupTCPServerSocket() failed", thread_args->port);

    for (;;) { // Run forever
        int clntSocket = AcceptTCPConnection(servSock);
        char buffer[BUFSIZE];

        // Receive message from client
        ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE-1, 0);
        if (numBytesRcvd < 0)
            DieWithSystemMessage("recv() failed");

        buffer[numBytesRcvd] = '\0';
        char *temp = strtok(buffer, "\t");

        if(temp != NULL) thread_args->file = temp; temp = strtok(NULL, "\t"); 
        if(temp != NULL) thread_args->previp = temp;

        printf("%s\n\n", thread_args->file);

        // Send received string and receive again until end of stream
        while (numBytesRcvd > 0) { // 0 indicates end of stream
            // Echo message back to client
            ssize_t numBytesSent = send(clntSocket, "Thanks", numBytesRcvd, 0);
            if (numBytesSent < 0)
                DieWithSystemMessage("send() failed");

            else if (numBytesSent != numBytesRcvd)
                DieWithUserMessage("send()", "sent unexpected number of bytes");

            else
                printf("Sending thank you note to %s\n", thread_args->previp);
            
            // See if there is more data to receive
            numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);

            if (numBytesRcvd < 0)
                DieWithSystemMessage("recv() failed");
        }

        close(clntSocket);
        break;
    }
    thread_out->file = strdup(thread_args->file);
    
    close(servSock);

    pthread_exit(thread_out);
}

void *client_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;

    printf("Sending data to: %s\n", thread_args->distantip);
    int sock = SetupTCPClientSocket(thread_args->localip, thread_args->port);
    if (sock < 0)
        DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");

    char buffer[BUFSIZE]; snprintf(buffer, BUFSIZE, "%s\t%s\t", thread_args->file, thread_args->localip);

    size_t bufferlength = strlen(buffer);
    ssize_t numBytes = send(sock, buffer, bufferlength, 0);
    if (numBytes < 0)
        DieWithSystemMessage("send() failed");
    else if (numBytes != bufferlength)
        DieWithUserMessage("send()", "sent unexpected number of bytes");

    unsigned int totalBytesRcvd = 0; // Count of total bytes received
    while(totalBytesRcvd < 1){
        char buffer[BUFSIZE];
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if (numBytes < 0)
            DieWithSystemMessage("recv() failed");
        else if (numBytes == 0)
            DieWithUserMessage("recv()", "connection closed prematurely");
        else{
            totalBytesRcvd += numBytes; // Keep tally of total bytes
            buffer[numBytes] = '\0';    // Terminate the string!
            printf("Received a thank you note from: %s\n", thread_args->distantip); break;
        }
    }

    close(sock); pthread_exit(thread_args);
}


char *readFileToString(const char *filename) {

    FILE *file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *string = (char *)malloc(file_size + 1);
    fread(string, 1, file_size, file);
    string[file_size] = '\0';

    fclose(file);
    return string;
}


int main(int argc, char *argv[]) {
    ThreadArgs thread_args, *thread_out;
    
    thread_args.distantip = argv[1];
    thread_args.port = argv[2];
    
    pthread_t server_tid, client_tid;

///////////////////////////////////////////////////////////
//In this block of code, you will find your local ip
    
    char host[256];
    gethostname(host, sizeof(host));
    struct hostent *host_entry;
    host_entry = gethostbyname(host);

    if (host_entry == NULL) {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }

thread_args.localip = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

///////////////////////////////////////////////////////////
    
    if (argc == 4) {
        thread_args.file = readFileToString(argv[3]); 
        printf("My IP address is: %s\n", thread_args.localip);
        
        pthread_create(&client_tid, NULL, &client_thread, (void*)&thread_args);
        pthread_join(client_tid, (void*) &thread_args);

        
        pthread_create(&server_tid, NULL, &server_thread, (void*)&thread_args);
        pthread_join(server_tid, (void**) &thread_out);

        printf("Goodbye!\n");
    }
    else if (argc == 3){
        printf("My IP address is: %s\n", thread_args.localip);

        pthread_create(&server_tid, NULL, &server_thread, (void*)&thread_args);
        pthread_join(server_tid, (void**) &thread_out);
        thread_args.file = thread_out->file;

        pthread_create(&client_tid, NULL, &client_thread, (void*)&thread_args);
        pthread_join(client_tid, (void*) &thread_args);    

        printf("Goodbye!\n");
    }

    return 0;
}