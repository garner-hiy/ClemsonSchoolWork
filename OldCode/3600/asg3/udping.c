// Member Names: AJ Garner, Mitchell Pohar
// Date: 10 April 2024
// Class: CPSC 3600
// Assignment: Assignment 3

// To Complile: gcc -Wall -g -o udping -pthread -std=gnu99 udping.c DieWithMessage.c AddressUtility.c
//              (or use makefile)
// To Run Server: ./udping -S -p <port number>
// To Run Client: ./udping -i <ping interval> -c <ping count> -s <size in bytes> -p <port number> <server ip>
//                or
//                ./udping -c <ping count> -s <size in bytes> -i <ping interval> -p <port number> -n <server ip>

// To create a compressed archived file:
// tar -cvzf asg3.tar.gz udping.c makefile DieWithMessage.c AddressUtility.c Practical.h

// To extract a compressed archived file:
// tar -xvzf asg3.tar.gz

// To list contents of a tar.gz file:
// tar -ztvf asg3.tar.gz

#include "Practical.h"

#define AMT_NSEC 1000000000
#define AMT_MSEC 1000
#define MAX_PACKET_SIZE 300

// struct to hold information for config options of ping 
typedef struct {
    int pingCount;
    int byteSize;
    int noPrint;
    int server;
    float pingInterval;
    char portNum[10];
    char serverIP[30];
} Config;
// global struct for configuration options
Config configStruct;

// struct to hold information for displaying statistics
typedef struct {
    double totalRTT;
    double minRTT;
    double maxRTT;
    int totalTime;
    int packetsTransmitted;
    int packetsReceived;
} Statistics;
// global struct for statistics 
Statistics statStruct;

//String which holds the string to send in packet
char *packetString;
struct addrinfo *servAddr; // list of server addresses
int sock; // socket for either client or server
int recievedpacket = 0; // variable used to notify server that a packet has been received
struct sockaddr_storage clntAddr; // Client Address
ssize_t numBytesRcvd; // Number of Bytes recieved to send back to the client

// mutex and conditional variables for pthread_cond_timedwait()
pthread_mutex_t mutexInitial = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condInitial = PTHREAD_COND_INITIALIZER;

// the time in which the client started sending packets
struct timespec starttime;

// prototypes of the helper function with descriptions below main
struct timespec newTimeSpec(int tv_sec, int tv_nsec, struct timespec oldTime);
double timeDifference(struct timespec oldTime, struct timespec newTime);
int packetslost(int packetsRecieved, int packetsTransmitted);
void sigint_handler(int signum);
void printStatistics();
void* sender(void* arg);
void* receiver(void* arg);

// main function for udping flow control
int main(int argc, char *argv[]) {
    
    // call to the signal function if user wants to end the program early with CTR C
    signal(SIGINT, sigint_handler); 
    int c; 
    
    // default values for options
    configStruct.pingCount = 0x7fffffff; 
    configStruct.pingInterval = 1.0; 
    strcpy(configStruct.portNum, "33333");  
    configStruct.byteSize = 12; 
    configStruct.noPrint = 0; 
    configStruct.server = 0; 
    
    // parse the command lines arguments
    while ((c = getopt(argc, argv, "c:i:p:s:nSh")) != -1) {
         switch (c) { 
            // count ping option - number of pings to send
            case 'c': configStruct.pingCount = atoi(optarg); break; 
            // interval ping option - time interval between pings 
            case 'i': configStruct.pingInterval = atof(optarg); break; 
            // port number option
            case 'p': strcpy(configStruct.portNum, optarg); break;
            // byte size option
            case 's': configStruct.byteSize = atoi(optarg); break; 
            // no printing option
            case 'n': configStruct.noPrint = 1; break; 
            // server option 
            case 'S': configStruct.server = 1; break; 
            // help option - lists options and displays use of command line
            case 'h': printf("Usage: udping [-c count] [-i interval] [-p port] [-s size] [-n] [-S] [serverIP]\n"); exit(0); 
            // unknown option
            case '?': 
                if (optopt == 'c' || optopt == 'i' || optopt == 'p' || optopt == 's') fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt)) fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt); 
                    return 1;
                }
            // default case
            default: abort();
        }
    }
    // retrieves server IP from command line
    if(!configStruct.server) strcpy(configStruct.serverIP, argv[optind]);

    // retrieving address information
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;
    addrCriteria.ai_socktype = SOCK_DGRAM;
    addrCriteria.ai_protocol = IPPROTO_UDP;
    
    // if server
    if(configStruct.server) {
        addrCriteria.ai_flags = AI_PASSIVE;
        getaddrinfo(NULL, configStruct.portNum, &addrCriteria, &servAddr);
    }
    // if client
    else {
        getaddrinfo(configStruct.serverIP, configStruct.portNum, &addrCriteria, &servAddr);
        fprintf(stderr, "Count%*d\n", 20, configStruct.pingCount);
        fprintf(stderr, "Size%*d\n", 21, configStruct.byteSize); 
        fprintf(stderr, "Interval%*.3f\n", 17, configStruct.pingInterval); 
        fprintf(stderr, "Port%*s\n", 21, configStruct.portNum);
        fprintf(stderr, "Server_ip%*s\n", 16, configStruct.serverIP);
        printf("\n");
    }

    // create UDP socket
    sock = socket(servAddr->ai_family, servAddr->ai_socktype, servAddr->ai_protocol);

    // run server if server is true
    if (configStruct.server) {
        if (bind(sock, servAddr->ai_addr, servAddr->ai_addrlen) < 0) DieWithSystemMessage("bind() failed");
        // free address list allocated by getaddrinfo()
        freeaddrinfo(servAddr);
    }
    if(configStruct.noPrint) printf("**********\n");

    // retrieves the starting time
    clock_gettime(CLOCK_REALTIME, &starttime);
    packetString = malloc(sizeof(char)*(MAX_PACKET_SIZE+1));

    // create threads and thread ID's for sender and receiver
    pthread_t senderThreadID, receiverThreadID;
    pthread_create(&senderThreadID, NULL, &sender, NULL);
    pthread_create(&receiverThreadID, NULL, &receiver, NULL);
    
    // join threads for sender and receiver
    pthread_join(senderThreadID, NULL);
    pthread_join(receiverThreadID, NULL);
    
    // print stats
    printStatistics();
    
    // free packetString allocated memory
    free(packetString);

    return 0; 
}

// helper function to calculate packets lost based on packets received and transmitted, and as a percentage
int packetslost(int packetsRecieved, int packetsTransmitted) {
    return ((double)(packetsTransmitted - packetsRecieved) / (double)packetsTransmitted) * 100;
}

// signal handler function to print statistics and exit
void sigint_handler(int signum) {
    printStatistics();
    exit(0);
}

// helper function that retrieves the difference between the new time and old time and returns in a double
double timeDifference(struct timespec oldTime, struct timespec newTime) {
    double old = (double)oldTime.tv_sec + ((double)oldTime.tv_nsec/(double)AMT_NSEC);
    double new = (double)newTime.tv_sec + ((double)newTime.tv_nsec/(double)AMT_NSEC);
    return new-old;
}

// helper function used to add seconds and milliseconds to the original timespec oldTime
struct timespec newTimeSpec(int tv_sec, int tv_nsec, struct timespec oldTime) {

    // adds the seconds to oldTime
    oldTime.tv_sec += tv_sec;
    // adds the nanoseconds together
    int nsec = oldTime.tv_nsec + tv_nsec;
    // if it detects nanosecond overflow, then it adds a second and removes it from the nanoseconds
    if(nsec > 999999999) {
        oldTime.tv_sec += 1;
        oldTime.tv_nsec = nsec - AMT_NSEC;
    }
    // else, the nanoseconds equals the addition
    else oldTime.tv_nsec = nsec;
    // returns time
    return oldTime;
}

// helper function to print statistics
void printStatistics() {

    // retrieves the finished time
    struct timespec finishtime;
    clock_gettime(CLOCK_REALTIME, &finishtime);
    statStruct.totalTime = timeDifference(starttime, finishtime) * 1000;

    printf("\n");

    // prints all of the information for the client
    if(!configStruct.server) {
        printf("%d packets transmitted, %d received, %d%% packet loss, time %d ms\n", 
        statStruct.packetsTransmitted, statStruct.packetsReceived, packetslost(statStruct.packetsReceived, statStruct.packetsTransmitted), statStruct.totalTime);
        printf("rtt min/avg/max = %.3f/%.3f/%.3f msec\n",
        statStruct.minRTT, (statStruct.totalRTT/statStruct.packetsReceived), statStruct.maxRTT);
    }
}

// pthread function to send ping packets
void* sender(void* arg) {
    
    // if server mode, it prepares to send the recieved packet back to the client
    if(configStruct.server) {
        for (;;) {
            if(recievedpacket) {
                recievedpacket = 0;
                // send received datagram back to the client
                sendto(sock, packetString, numBytesRcvd, 0, (struct sockaddr *) &clntAddr, sizeof(clntAddr));
            }
        }
    }

    // if client mode, first it sets up variables and fills the buffer to send to the server
    statStruct.packetsTransmitted = 0;
    int packetCount = 0;
    for(packetCount = 0; packetCount < configStruct.byteSize; packetCount++){
        packetString[packetCount] = 'w';
    }
    // null terminate the packet string
    packetString[packetCount+1] = '\0';

    // sends each packet to the server, calculating the appropriate time when to send and waiting until it is time
    for(int intervalCount = 1; intervalCount <= configStruct.pingCount; intervalCount++) {
        double pingtime = (intervalCount - 1) * configStruct.pingInterval;
        struct timespec newTime = newTimeSpec((int)pingtime, (int)((pingtime - (int)pingtime)*1000000000), starttime);

        pthread_mutex_lock(&mutexInitial);
        pthread_cond_timedwait(&condInitial, &mutexInitial, &newTime);
        pthread_mutex_unlock(&mutexInitial);

        int strlength = strlen(packetString);

        // send string to server
        sendto(sock, packetString, strlength, 0, servAddr->ai_addr, servAddr->ai_addrlen);
        statStruct.packetsTransmitted++;
    }
    return NULL;
}

// pthread function to receive ping packets and calculate round-trip times
void* receiver(void* arg) {

    // if server mode, it prepares to recieve a packet from the client
    if(configStruct.server) {
        for (;;) { 
            socklen_t clntAddrLen = sizeof(clntAddr);
            numBytesRcvd = recvfrom(sock, packetString, MAX_PACKET_SIZE, 0, (struct sockaddr *) &clntAddr, &clntAddrLen);
            recievedpacket = 1;
        }
    }

    // if client mode, it prepares all of the variables necessary to recieve the packet back from the server
    int tempInterval;
    statStruct.maxRTT = -1;
    statStruct.minRTT = -1;
    statStruct.totalRTT = 0;
    statStruct.packetsReceived = 0;
    statStruct.totalTime = 0;
    ssize_t numBytes;

    // iterates through recieving new packets until it gets to the maximum ping count
    for (int counter = 0; counter < configStruct.pingCount; counter++) {
        // receive a response
        tempInterval = counter+1;
        double pingtime = (tempInterval - 1) * configStruct.pingInterval;
        struct timespec sendtime = newTimeSpec((int)pingtime, (int)((pingtime - (int)pingtime)*1000000000), starttime);

        // source server address
        struct sockaddr_storage fromAddr;
        socklen_t fromAddrLen = sizeof(fromAddr);
        char buffer[MAX_PACKET_SIZE + 1];
        numBytes = recvfrom(sock, buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *) &fromAddr, &fromAddrLen);

        if(numBytes > 0) statStruct.packetsReceived++;

        struct timespec recvtime;
        clock_gettime(CLOCK_REALTIME, &recvtime);

        double time = timeDifference(sendtime, recvtime);

        // calculates min and max time
        if (time < statStruct.minRTT) statStruct.minRTT = time;
        else if (statStruct.minRTT < 0) statStruct.minRTT = time;
        if (time > statStruct.maxRTT) statStruct.maxRTT = time;
        
        // increment the totalRTT variable by elapsed time 
        statStruct.totalRTT += time;
        // if user did not use noPrint option, print the packet info line by line 
        if (configStruct.noPrint == 0) printf("%4d%5ld%7.3f\n", tempInterval, numBytes, time);
    }
    freeaddrinfo(servAddr);
    return NULL;
}