// Member Names: AJ Garner, Mitchell Pohar
// Date: 22 March 2024
// Class: CPSC 3600
// Assignment: Assignment 2

// To Compile: gcc -o client -std=gnu99 client.c DieWithMessage.c TCPClientUtility.c
//             (or use makefile)
// To Run Client: ./client <Server IP address> <port>

// To create a compressed archived file:
// tar -cvzf asg2.tar.gz client.c server.c makefile DieWithMessage.c TCPClientUtility.c TCPServerUtility.c AddressUtility.c Practical.h

// To extract a compressed archived file:
// tar -xvzf asg2.tar.gz

// To list contents of a tar.gz file:
// tar -ztvf asg2.tar.gz

// libraries needed to run this program
#include "Practical.h"

//This function will save the file into the current directory
//by creating a new file and saving everything to it
void saveFile(const char *fileName, const char *data) {
    //make new file in write only
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error saving file");
        exit(EXIT_FAILURE);
    }
    //copy the data
    fputs(data, file);
    //close the file
    fclose(file);
}


int main(int argc, char *argv[]){

    //variables needed
    char menuChoice[20];
    int menuTries = 0;
    char buffer[BUFSIZE];//what will be passed to the server
    char tempBuffer[BUFSIZE];//what is recieved from the server
    int checkingTwo = 0;//for error checking username before downloading
    int onlyOnce = 0;//used for username validation 

    //This checks for the correct CLAs
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <distant_ip> <port> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //storing the information needed
    char* serverIP = argv[1];
    char* clientPort = argv[2];
    char username[20];
    char fileName[30];

    //setting up the socket for the server
    int sock = SetupTCPClientSocket(serverIP, clientPort);
    if (sock < 0) DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");


 
    //the infinite while loop is needed for keeping the program going if the user wants to
    while(1){

        //menu
        printf("Select an action from the menu:\n");
        printf("1. Request file listing\n");
        printf("2. Download file\n");
        printf("3. List all downloads\n");
        printf("4. Exit\n\n");

        
        scanf("%s", menuChoice);

        //this while loop checks that the user is entering the correct choices 
        while(menuChoice[0] != '1' && menuChoice[0] != '2' && menuChoice[0] != '3' && menuChoice[0] != '4'){

            if(menuTries < 4){//four tires and you are done
                printf("Not a valid menu choice\nUsage: 1 through 4\n");
                scanf("%s", menuChoice);
                menuTries++;
            }
            else{
                printf("Too many tries\nGoodbye!\n");
                exit(EXIT_FAILURE);//closes the program
            }
        }

        switch(menuChoice[0]){//grabbing the first element off the array
        /*
        Case 1 deals with listing the files on the server, it will ask for a username and 
        give back the list from the server. It will ask for the username once and it will
        send an event check to case 2.
        */
            case '1': 
                checkingTwo++;//used for error checking case 2

                // if this is the first time in case 1, ask for username from user
                if (onlyOnce == 0){
                    printf("Please enter your username\n");
                    scanf("%19s", username);
                }
                snprintf(buffer, BUFSIZE, "%s%s", menuChoice, username);//storing to the buffer for passing

                size_t bufferlength = strlen(buffer);//needed for send and recv functions
                ssize_t numBytes = send(sock, buffer, bufferlength, 0);//sending and error checking

                if (numBytes < 0) DieWithSystemMessage("send() failed in option 1");
                else if (numBytes != bufferlength) DieWithUserMessage("send()", "sent unexpected number of bytes in option 1");
                onlyOnce++;//keeps username asked once only

                unsigned int totalBytesRcvd = 0;//error checking for recv()
                
                while (totalBytesRcvd < 1) {
                    numBytes = recv(sock, tempBuffer, BUFSIZE - 1, 0);
                    if (numBytes < 0) DieWithSystemMessage("recv() failed in option 1");
                    else if (numBytes == 0) DieWithUserMessage("recv()", "connection closed prematurely in option 1");
                    else{//everything is fine...
                        printf("Listing received from server:\n");
                        printf("%s\n", tempBuffer);
                        buffer[0] = '\0';
                        memset(tempBuffer, 0, sizeof(tempBuffer));
                        break;
                    }
                }

                break;

            case '2':
            /*
            Case 2 will ask for what file you want to download and send that to the server, it will
            then take that file back from the server and store it into your directory. It will also
            print out to terminal what is in the file and have it formatted as well. It will check
            that you have listed the files first and thus have entered your username.
            */
                if(checkingTwo == 0){//can't download a file before knowing what's on the server
                    printf("You must list the files first (option 1), before downloading anything\n");
                    break;
                }

                printf("Enter filename you would like to download:\n");
                scanf("%s", fileName);

                snprintf(buffer, BUFSIZE, "%s%s", menuChoice, fileName);
                
                bufferlength = strlen(buffer);//error checking
                numBytes = send(sock, buffer, bufferlength, 0);//sending and error checking

                if (numBytes < 0)
                    DieWithSystemMessage("send() failed in option 2");
                else if (numBytes != bufferlength)
                    DieWithUserMessage("send()", "sent unexpected number of bytes in option 2");


                totalBytesRcvd = 0;//error checking

                while (totalBytesRcvd < 1) {
                    numBytes = recv(sock, tempBuffer, BUFSIZE - 1, 0);
                    if (numBytes < 0) DieWithSystemMessage("recv() failed in option 2");
                    else if (numBytes == 0) DieWithUserMessage("recv()", "connection closed prematurely in option 2");
                    else if (strcmp(tempBuffer, "File Does Not Exist\n") == 0){
                        printf("%sPlease try again...\n\n", tempBuffer);
                        break;
                    }
                    else{
                        printf("Received %s\nDisplaying %s:\n\n", fileName, fileName);
                        printf("%s\n\n", tempBuffer);
                        saveFile(fileName, tempBuffer);
                        buffer[0] = '\0';
                        memset(tempBuffer, 0, sizeof(tempBuffer));
                        break;
                    }
                }
                break;

            case '3':
            /*
            Case 3 will send a message to the server asking for the log of users and the downloaded files.
            */
                snprintf(buffer, BUFSIZE, "%s", menuChoice);

                bufferlength = strlen(buffer);//error checking
                numBytes = send(sock, buffer, bufferlength, 0);//sending and error checking

                if (numBytes < 0) DieWithSystemMessage("send() failed in option 3");
                else if (numBytes != bufferlength) DieWithUserMessage("send()", "sent unexpected number of bytes in option 3");

                totalBytesRcvd = 0;//error checking

                while (totalBytesRcvd < 1) {
                    numBytes = recv(sock, tempBuffer, BUFSIZE - 1, 0);
                    if (numBytes < 0)
                        DieWithSystemMessage("recv() failed in option 3");
                    else if (numBytes == 0)
                        DieWithUserMessage("recv()", "connection closed prematurely in option 3");
                    else{
                        printf("Listing all downloads\n");
                        printf("%s\n", tempBuffer);
                        buffer[0] = '\0';
                        memset(tempBuffer, 0, sizeof(tempBuffer));
                        break;
                    }
                }
                break;

            case '4':
            /*
            Case 4 simplies sends a message to the server, allowing the server to terminate connection.
            It will then just exit the program for the client.
            */
                snprintf(buffer, BUFSIZE, "%s", menuChoice);

                bufferlength = strlen(buffer);//error checking
                numBytes = send(sock, buffer, bufferlength, 0);//sending and error checking

                if (numBytes < 0) DieWithSystemMessage("send() failed in option 4");
                else if (numBytes != bufferlength) DieWithUserMessage("send()", "sent unexpected number of bytes in option 4");

                totalBytesRcvd = 0;//error checking

                printf("Goodbye!!\n");
                close(sock);
                exit(EXIT_SUCCESS);
                
                while (totalBytesRcvd < 1) {
                    numBytes = recv(sock, tempBuffer, BUFSIZE - 1, 0);
                    if (numBytes < 0) DieWithSystemMessage("recv() failed in option 4");
                    else if (numBytes == 0) DieWithUserMessage("recv()", "connection closed prematurely in option 4");
                    else{
                        printf("Goodbye!!\n");
                        close(sock);
                        exit(EXIT_SUCCESS);
                    }
                }
                break;
        }
    }
    return 0;
}
