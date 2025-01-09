#ifndef PRACTICAL_H_
#define PRACTICAL_H_

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

enum sizeConstants {
  MAXSTRINGLENGTH = 128,
  BUFSIZE = 1024,
};

struct FileList {
    char* formattedFileList;
    char** fileList;
    size_t numFiles;
};

struct DATA{
    int socket;
    char clientAddress[20];
    char downloadLog[BUFSIZE];
    struct FileList fileData;
};

// Checks to see if fileName exist within the current directory
bool doesFileExist(char* fileName, char** fileList, size_t numFiles, char* log);
// Opens selected file and saves content to a string
char* openFile(const char* fileName);
// Takes away the first position in the buffer
char* minusMenuOption(char* incomingBuffer);
// Retrieves list of files in current directory
struct FileList getFileList();
// Handle error with user msg
void DieWithUserMessage(const char *msg, const char *detail);
// Handle error with sys msg
void DieWithSystemMessage(const char *msg);
// Print socket address
void PrintSocketAddress(const struct sockaddr *address, char *returnedAddress);
// Test socket address equality
bool SockAddrsEqual(const struct sockaddr *addr1, const struct sockaddr *addr2);
// Create, bind, and listen a new TCP server socket
int SetupTCPServerSocket(const char *service);
// Accept a new TCP connection on a server socket
int AcceptTCPConnection(int serverSocket, struct DATA* data);
// Handle new TCP client
void HandleTCPClient(int clientSocket, struct DATA* data);
// Create and connect a new TCP client socket
int SetupTCPClientSocket(const char *server, const char *service);

#endif // PRACTICAL_H_