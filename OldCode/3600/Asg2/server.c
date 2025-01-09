// Member Names: AJ Garner, Mitchell Pohar
// Date: 13 March 2024
// Class: CPSC 3600
// Assignment: Assignment 2

// To Compile: gcc -o fileserver -std=gnu99 server.c DieWithMessage.c TCPServerUtility.c AddressUtility.c -pthread
//             (or use makefile)
// To Run Client: ./fileserver <port>

// To create a compressed archived file:
// tar -cvzf asg2.tar.gz client.c server.c makefile DieWithMessage.c TCPClientUtility.c TCPServerUtility.c AddressUtility.c Practical.h

// To extract a compressed archived file:
// tar -xvzf asg2.tar.gz

// To list contents of a tar.gz file:
// tar -ztvf asg2.tar.gz

// libraries needed to run this program
#include "Practical.h"

// define a mutex for synchonizing access to the data struct
pthread_mutex_t dataMutex = PTHREAD_MUTEX_INITIALIZER;

// Function to retrieve file list
struct FileList getFileList() {
    // Initialize local variables
    struct dirent *directoryEntry;
    struct stat fileStat;
    struct FileList fileData;

    // Allocate memory for an empty string and initialize as an empty string
    fileData.formattedFileList = malloc(1);
    fileData.formattedFileList[0] = '\0';

    // Open current directory
    DIR *currentDirectory = opendir(".");
    if (currentDirectory == NULL) {
        perror("Could Not Open Current Directory");
        exit(EXIT_FAILURE);
    }
    
    // Initialize variables for holding file list
    fileData.fileList = NULL;
    fileData.numFiles = 0;

    // Iterate through directory entries
    while ((directoryEntry = readdir(currentDirectory)) != NULL) {
        if (directoryEntry->d_type == DT_REG) {
            if (strstr(directoryEntry->d_name, ".txt") != NULL ||
                strstr(directoryEntry->d_name, ".c") != NULL ||
                strstr(directoryEntry->d_name, ".h") != NULL) {
                
                // Skip the rest of the logic if it cannot get the stats from the file
                if (stat(directoryEntry->d_name, &fileStat) == -1) {
                    perror("Unable to get stats");
                    continue;
                }
                
                // Calculate the length of the formatted string
                size_t tempStringSize = snprintf(NULL, 0, "%-20s%10ld bytes\n", directoryEntry->d_name, fileStat.st_size);

                // Reallocate memory to accommodate the new string length
                fileData.formattedFileList = realloc(fileData.formattedFileList, strlen(fileData.formattedFileList) + tempStringSize + 1);
                if (fileData.formattedFileList == NULL) {
                    perror("Memory re-allocation failed");
                    exit(EXIT_FAILURE);
                }

                // Format the string into formattedFileList
                snprintf(fileData.formattedFileList + strlen(fileData.formattedFileList), tempStringSize + 1, "%-20s%10ld bytes\n", directoryEntry->d_name, fileStat.st_size);

                // Reallocate memory for file list array
                fileData.fileList = realloc(fileData.fileList, (fileData.numFiles + 2) * sizeof(char*));
                if (fileData.fileList == NULL) {
                    perror("Memory re-allocation failed");
                    exit(EXIT_FAILURE);
                }

                // Allocate memory for filename and size string and copy them
                fileData.fileList[fileData.numFiles] = malloc(strlen(directoryEntry->d_name) + 1);
                if (fileData.fileList[fileData.numFiles] == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                strcpy(fileData.fileList[fileData.numFiles], directoryEntry->d_name);
                
                char sizeString[20]; // Assuming a maximum size string length
                sprintf(sizeString, "%ld bytes", fileStat.st_size);
                fileData.fileList[fileData.numFiles + 1] = malloc(strlen(sizeString) + 1);
                if (fileData.fileList[fileData.numFiles + 1] == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                strcpy(fileData.fileList[fileData.numFiles + 1], sizeString);

                // Increment the number of files
                fileData.numFiles += 2;
            }
        }
    }
    
    // Close current directory
    closedir(currentDirectory);

    return fileData;
}

// Function to free memory allocated for file list
void freeFileList(struct FileList fileData) {
    free(fileData.formattedFileList);
    for (size_t i = 0; i < fileData.numFiles; ++i) {
        free(fileData.fileList[i]);
    }
    free(fileData.fileList);
}

// Helper Function to print string array for debugging purposes
void printFileList(struct FileList fileData) {
    for (size_t i = 0; i < fileData.numFiles; ++i) {
        printf("%s\n", fileData.fileList[i]);
    }
}

// thread helper funtion to accept and handle client logic on the server
void* clientHandler(void* dataStruct){
    struct DATA* data = (struct DATA*)dataStruct;
    
    // Accept a connection from a client computer
    int clientSocket = AcceptTCPConnection(data->socket, data);

    // Processing logic of a connected client
    HandleTCPClient(clientSocket, data);
    close(clientSocket);

}

int main(int argc, char *argv[]){

    struct DATA data;
    data.fileData = getFileList();
    //printf("%s", data.fileData.formattedFileList);

    //printf("\nFile List:\n");
    //printFileList(data.fileData);
    
    // if there are not two arguments in the command line, programs fails with error message
    if(argc != 2) DieWithUserMessage("Did Not Receive Required Parameter", "<Server Port>");

    char *port = argv[1];

    // create socket for incoming connections
    int serverSocket = SetupTCPServerSocket(port);
    data.socket = serverSocket;
    if (data.socket < 0) DieWithUserMessage("SetupTCPServerSocket() failed", "port is not available");

    // declaring pthread ID
    pthread_t clientHandlerID;

    // infinite for loop accepting and handling of client connection
    for(;;){

        pthread_create(&clientHandlerID, NULL, &clientHandler, (void*)&data);
        pthread_join(clientHandlerID, NULL);

    }
    // NOT REACHED
    close(serverSocket);
    
    freeFileList(data.fileData);
    return 0;
}