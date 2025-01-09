
COMPILER = gcc
OPTIONS = -Wall
PROGRAM = LAB4

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)  input.txt

$(PROGRAM): driver.c functions.c
	$(COMPILER) $(OPTIONS) driver.c functions.c -o $(PROGRAM) 

clean:
	rm -f $(PROGRAM)
