# Name: Mitchell L. Pohar
# Date: 13 March 2024
# Class: CPSC 3600
# Assignment: Assignment 2


# To compile: make
# To clean: make clean


compile:
	gcc -o fileserver -std=gnu99 server.c DieWithMessage.c TCPServerUtility.c AddressUtility.c -pthread
	gcc -o client -std=gnu99 client.c DieWithMessage.c TCPClientUtility.c

clean:
	rm fileserver
	rm client