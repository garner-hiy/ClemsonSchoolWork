COMPILER = gcc
OPTIONS = -Wall -g
PROGRAM = LAB7

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) lab7.c

$(PROGRAM): lab7.c
	$(COMPILER) $(OPTIONS) lab7.c -o $(PROGRAM) 

clean:
	rm -f $(PROGRAM)

