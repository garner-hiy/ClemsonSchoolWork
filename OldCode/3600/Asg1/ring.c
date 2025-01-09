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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    char *file;
    char *localip;
    char *distantip;
    char *previp;
    char *port;
} ThreadArgs;

void *server_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    ThreadArgs *thread_out = malloc(sizeof(ThreadArgs));

    int servSock = SetupTCPServerSocket(thread_args->port);
    if (servSock < 0)
        DieWithUserMessage("SetupTCPServerSocket() failed", thread_args->port);

    for (;;) {
        int clntSocket = AcceptTCPConnection(servSock);
        char buffer[BUFSIZE];

        ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE - 1, 0);
        if (numBytesRcvd < 0)
            DieWithSystemMessage("recv() failed");

        buffer[numBytesRcvd] = '\0';
        char *temp = strtok(buffer, "\t");

        pthread_mutex_lock(&mutex);
        if (temp != NULL)
            thread_args->file = strdup(temp);
        temp = strtok(NULL, "\t");
        if (temp != NULL)
            thread_args->previp = strdup(temp);
        pthread_mutex_unlock(&mutex);

        printf("%s\n\n", thread_args->file);

        while (numBytesRcvd > 0) {
            ssize_t numBytesSent = send(clntSocket, "Thanks", numBytesRcvd, 0);
            if (numBytesSent < 0)
                DieWithSystemMessage("send() failed");
            else if (numBytesSent != numBytesRcvd)
                DieWithUserMessage("send()", "sent unexpected number of bytes");
            else
                printf("Sending thank you note to %s\n", thread_args->previp);

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
    ThreadArgs *thread_out = malloc(sizeof(ThreadArgs));

    printf("Sending data to: %s\n", thread_args->distantip);
    int sock = SetupTCPClientSocket(thread_args->distantip, thread_args->port);
    if (sock < 0)
        DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");

    char buffer[BUFSIZE];
    snprintf(buffer, BUFSIZE, "%s\t%s\t", thread_args->file, thread_args->localip);

    size_t bufferlength = strlen(buffer);
    ssize_t numBytes = send(sock, buffer, bufferlength, 0);
    if (numBytes < 0)
        DieWithSystemMessage("send() failed");
    else if (numBytes != bufferlength)
        DieWithUserMessage("send()", "sent unexpected number of bytes");

    unsigned int totalBytesRcvd = 0;
    while (totalBytesRcvd < 1) {
        numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
        if (numBytes < 0)
            DieWithSystemMessage("recv() failed");
        else if (numBytes == 0)
            DieWithUserMessage("recv()", "connection closed prematurely");
        else {
            pthread_mutex_lock(&mutex);
            thread_args->file = strdup(buffer);
            pthread_mutex_unlock(&mutex);
            printf("Received a thank you note from: %s\n", thread_args->distantip);
            break;
        }
    }

    close(sock);
    pthread_exit(thread_args);
}

char *readFileToString(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *string = (char *)malloc(file_size + 1);
    fread(string, 1, file_size, file);
    string[file_size] = '\0';

    fclose(file);
    return string;
}

char* fetchIPAddress() {
    // Linux command to retrieve IP address
    const char* linuxCommand = "ifconfig | grep 'inet ' | awk '{print $2}'";

    // Open a pipe and execute the command
    FILE* commandPtr = popen(linuxCommand, "r");
    if (!commandPtr) {
        perror("Failed to execute Linux command");
        exit(EXIT_FAILURE);
    }

    // Read IP address from the command output
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), commandPtr) != NULL) {
        size_t bufferLength = strlen(buffer);
        if (bufferLength > 0 && buffer[bufferLength - 1] == '\n') {
            buffer[bufferLength - 1] = '\0';
        }

        // Allocate memory for the IP address and copy the value
        char* ipAddress = strdup(buffer);

        // Close the command pipe
        pclose(commandPtr);

        return ipAddress;
    }

    // Close the command pipe and return NULL if no IP address is found
    pclose(commandPtr);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <distant_ip> <port> [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ThreadArgs thread_args;
    thread_args.distantip = argv[1];
    thread_args.port = argv[2];

/*/////////////////////////////////

    //trying to get local ip address here
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    char host[256];
    gethostname(host, sizeof(host));

    if (getaddrinfo(host, NULL, &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
thread_args.localip = inet_ntoa(addr->sin_addr);

freeaddrinfo(res);

////////////////////////////*/
    thread_args.localip = fetchIPAddress();

    if (argc == 4) {
        thread_args.file = readFileToString(argv[3]);
        printf("My IP address is: %s\n", thread_args.localip);

        pthread_t client_tid, server_tid;
        pthread_create(&client_tid, NULL, &client_thread, (void *)&thread_args);
        pthread_join(client_tid, (void **)&thread_args);

        pthread_create(&server_tid, NULL, &server_thread, (void *)&thread_args);
        ThreadArgs *thread_out;
        pthread_join(server_tid, (void **)&thread_out);

        free(thread_out->file);
        free(thread_out);

        printf("Goodbye!\n");
    } else if (argc == 3) {
        printf("My IP address is: %s\n", thread_args.localip);

        pthread_t server_tid, client_tid;
        pthread_create(&server_tid, NULL, &server_thread, (void *)&thread_args);
        ThreadArgs *thread_out;
        pthread_join(server_tid, (void **)&thread_out);

        pthread_mutex_lock(&mutex);
        thread_args.file = strdup(thread_out->file);
        pthread_mutex_unlock(&mutex);

        pthread_create(&client_tid, NULL, &client_thread, (void *)&thread_args);
        pthread_join(client_tid, (void **)&thread_args);

        free(thread_args.file);

        printf("Goodbye!\n");
    }

    return 0;
}
