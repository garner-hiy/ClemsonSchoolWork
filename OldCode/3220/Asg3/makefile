# Member Names: AJ Garner, Mitchell Pohar
# Date: 15 April 2024
# Class: CPSC 3220
# Assignment: Homework 3


# To compile: make
# To run: make run01
#         or
#         make run02
#         or
#         make run1
#         or
#         make run2
#         or
#         make run3

# To clean: make clean


compile:
	gcc -g tfs_1.c tfs_2.c tfs_driver1.c -o tfs_driver1.out
	gcc -g tfs_1.c tfs_2.c tfs_driver2.c -o tfs_driver2.out
	gcc -g grtfs_1.c grtfs_2.c grtfs_driver1.c -o grtfs_driver1.out
	gcc -g grtfs_1.c grtfs_2.c grtfs_driver2.c -o grtfs_driver2.out
	gcc -g grtfs_1.c grtfs_2.c grtfs_driver3.c -o grtfs_driver3.out

# Run original 256 trivial file system with driver 1
run01:
	./tfs_driver1.out

# Run original 256 trivial file system with driver 2
run02:
	./tfs_driver2.out

# Run new 4096 great file system with driver 1
run1:
	./grtfs_driver1.out

# Run new 4096 great file system with driver 2
run2:
	./grtfs_driver2.out

# Run new 4096 great file system with driver 3
run3:
	./grtfs_driver3.out

# Clean all .out files from the directory
clean:
	rm -rf *.out