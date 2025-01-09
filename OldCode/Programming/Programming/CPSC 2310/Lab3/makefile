COMPILER = gcc
OPTIONS = -Wall
PROGRAM = LAB3

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) classdata.csv output.txt

$(PROGRAM): driver.c functions.c
	$(COMPILER) $(OPTIONS) driver.c functions.c -o $(PROGRAM) 

clean:
	rm -f $(PROGRAM)

