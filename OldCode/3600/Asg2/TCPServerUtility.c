#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "Practical.h"

static const int MAXPENDING = 5; // Maximum outstanding connection requests
// define a mutex for synchonizing access to the data struct
pthread_mutex_t dMutex = PTHREAD_MUTEX_INITIALIZER;

char* minusMenuOption(char* incomingBuffer){
  char* buffer = incomingBuffer; // Original string
  // Allocate memory for the new string
  size_t originalLength = strlen(buffer);
  char *newString = malloc(originalLength); // Allocate enough memory for the new string
  if (newString == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  // Use sscanf to skip the first character and copy the rest to newString
  if (sscanf(buffer, "1%s", newString) != 1) {
    perror("Error in parsing string");
    exit(EXIT_FAILURE);
  }
  return newString;
}

bool doesFileExist(char* fileName, char** fileList, size_t numFiles, char* log){
  // iterate through the fileList array to see if the fileName exists
  for(int i = 0; i < numFiles; i++){
    if(strcmp(fileName, fileList[i]) == 0) {
      sprintf(log, "%-15s %10s\n", fileName, fileList[i+1]);
      return true;
    }
  }
  return false;
}

char* openFile(const char* fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) DieWithUserMessage("Error opening file: %s\n", fileName);

    // Find out the size of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *fileContents = (char*)malloc((fileSize + 1) * sizeof(char));
    if (fileContents == NULL) DieWithSystemMessage("Memory allocation for openFile() failed\n");

    // Read the contents of the file into fileContents
    size_t bytesRead = fread(fileContents, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
      free(fileContents);
      fclose(file);
      DieWithUserMessage("Error reading file: %s\n", fileName);
    }

    // Add null terminator to make it a valid C string
    fileContents[bytesRead] = '\0';

    // Close the file
    fclose(file);

    return fileContents;
}

int SetupTCPServerSocket(const char *service) {
  // Construct the server address structure
  struct addrinfo addrCriteria;                   // Criteria for address match
  memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  addrCriteria.ai_flags = AI_PASSIVE;             // Accept on any address/port
  addrCriteria.ai_socktype = SOCK_STREAM;         // Only stream sockets
  addrCriteria.ai_protocol = IPPROTO_TCP;         // Only TCP protocol

  struct addrinfo *servAddr; // List of server addresses
  int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
  if (rtnVal != 0)
    DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

  int servSock = -1;
  for (struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next) {
    // Create a TCP socket
    servSock = socket(addr->ai_family, addr->ai_socktype,
        addr->ai_protocol);
    if (servSock < 0)
      continue;       // Socket creation failed; try next address

    // Bind to the local address and set socket to listen
    if ((bind(servSock, addr->ai_addr, addr->ai_addrlen) == 0) &&
        (listen(servSock, MAXPENDING) == 0)) {
      // Print local address of socket
      struct sockaddr_storage localAddr;
      socklen_t addrSize = sizeof(localAddr);
      if (getsockname(servSock, (struct sockaddr *) &localAddr, &addrSize) < 0)
        DieWithSystemMessage("getsockname() failed");
      break;       // Bind and listen successful
    }

    close(servSock);  // Close and try again
    servSock = -1;
  }

  // Free address list allocated by getaddrinfo()
  freeaddrinfo(servAddr);

  return servSock;
}

int AcceptTCPConnection(int serverSocket, struct DATA* data) {
  struct sockaddr_storage clntAddr; // Client address
  // Set length of client address structure (in-out parameter)
  socklen_t clntAddrLen = sizeof(clntAddr);

  // Wait for a client to connect
  int clntSock = accept(serverSocket, (struct sockaddr *) &clntAddr, &clntAddrLen);
  if (clntSock < 0) DieWithSystemMessage("accept() failed");

  // clntSock is connected to a client!
  pthread_mutex_lock(&dMutex);
  PrintSocketAddress((struct sockaddr *) &clntAddr, data->clientAddress);
  pthread_mutex_unlock(&dMutex);

  return clntSock;
}

void HandleTCPClient(int clientSocket, struct DATA* dataStruct) {
  char buffer[BUFSIZE]; // Buffer
  char* username = "No Username Was Entered";
  char* fileName = "No File Name Was Entered";
  char* fileContents = "File Does Not Exist\n";
  char log[75];
  char destination[100];

  // Receive message from client
  ssize_t numBytesRcvd = recv(clientSocket, buffer, BUFSIZE, 0);
  if (numBytesRcvd < 0) DieWithSystemMessage("recv() failed");

  ssize_t numBytesSent = 0;

  // Loop until client disconnects (or other termination condition)
  while (buffer[0] != '4') {

    switch(buffer[0]){
      case '1': 
        // initializing username from buffer
        username = minusMenuOption(buffer);
        
        // print to server command line
        fputs("Connected to: ", stdout);
        fputs(username, stdout);
        fputs(", IP: ", stdout);
        fputs(dataStruct->clientAddress, stdout);
        fputc('\n', stdout);
        fputc('\t', stdout);
        fputs(username, stdout);
        fputs(" requested file listing\n", stdout);
        
        // sending list of files in current directory to client
        numBytesSent = send(clientSocket, dataStruct->fileData.formattedFileList, numBytesRcvd, 0);
        if (numBytesSent < 0) DieWithSystemMessage("send() in menu option 1 failed");
        else if (numBytesSent != numBytesRcvd) DieWithUserMessage("send() in menu option 1: ", "sent unexpected number of bytes");
        break;

      case '2': 
        // initializing fileName from buffer
        fileName = minusMenuOption(buffer);

        // print to server command line
        fputc('\t', stdout);
        fputs(username, stdout);
        fputs(" requested download: ", stdout);
        fputs(fileName, stdout);
        fputc('\n', stdout);

        // opening file and saving contents to string
        if (doesFileExist(fileName, dataStruct->fileData.fileList, dataStruct->fileData.numFiles, log)) {
          fileContents = openFile(fileName);
          numBytesSent = send(clientSocket, fileContents, numBytesRcvd, 0);
          free(fileContents);
        }
        else {
          fileContents = "File Does Not Exist\n";
          numBytesSent = send(clientSocket, fileContents, numBytesRcvd, 0);
        }
        if (numBytesSent < 0) DieWithSystemMessage("send() in menu option 2 failed");
        else if (numBytesSent != numBytesRcvd) DieWithUserMessage("send() in menu option 2: ", "sent unexpected number of bytes");
        else {
          // print to server command line
          fputs("Sent ", stdout);
          fputs(fileName, stdout);
          fputs(" to ", stdout);
          fputs(username, stdout);
          fputc('\n', stdout);

          sprintf(destination, "%-10s %10s", username, log);
          
          pthread_mutex_lock(&dMutex);
          strcat(dataStruct->downloadLog, destination);
          pthread_mutex_unlock(&dMutex);
        }
        break;

      case '3': 
        fputc('\t', stdout);
        fputs(username, stdout);
        fputs(" requested listing of dowloads\n", stdout);

        size_t logLength = strlen(dataStruct->downloadLog);
        numBytesSent = send(clientSocket, dataStruct->downloadLog, logLength, 0);

        if (numBytesSent < 0) DieWithSystemMessage("send() in menu option 3 failed");
        else if (numBytesSent != numBytesRcvd) DieWithUserMessage("send() in menu option 3: ", "sent unexpected number of bytes");
        else {
          fputs("Sent listing of downloads to ", stdout);
          fputs(username, stdout);
          fputc('\n', stdout);
        }
        break;
    }

    // Receive next message from client
    numBytesRcvd = recv(clientSocket, buffer, BUFSIZE, 0);
    if (numBytesRcvd < 0) DieWithSystemMessage("recv() failed");
  }
  //checking for 4
  if(buffer[0] == '4') {
    fputs("Connect with ", stdout);
    fputs(username, stdout);
    fputs(" terminated\n\n", stdout);
  }
  close(clientSocket); // Close client socket
}