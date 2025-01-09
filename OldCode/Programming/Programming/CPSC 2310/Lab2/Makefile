# Config, just variables
# These are the basic variables needed for the makefile
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out

# This block of code will look for all files within the diretory 
# that match the file type which is .c
# it will be used to make the objects files needed
C_SRCS := \
	$(wildcard *.c) \
	$(wildcard src/*.c) \
	$(wildcard src/**/*.c) \

# This block of code will look for all files within the diretory 
# that match the file type which is .h
# it will be used to make the objects files needed
HDRS := \
	$(wildcard *.h) \
	$(wildcard src/*.h) \
	$(wildcard src/**/*.h) \

# This gives the object files the wildcard rule
# It will also make them in a folder called bin
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

# default target used to run everything
all: build
	@echo "All Done!"

#link all built objects
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

# This is a target that will put these kinds of files
# in the folder of bin
# It will also move the files to bin instead of putting
# thing next to the source file
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# This is a target that will put these kinds of files
# in the folder of bin
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# This will clean up out files and allow for fresh 
# builds and quick executions
clean:
	rm -f $(TARGET)
	rm -rf bin

# This is the target of the make that will run all commands line arguments 
run: build
	./$(TARGET) input.txt output.txt

# This target will show us the files that were found
# when running the wildcard commands
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"