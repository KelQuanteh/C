# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = main.c arff.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = program

# Default target (executable)
all: $(EXEC)

# Linking the object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compiling individual source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
