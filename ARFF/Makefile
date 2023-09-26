CC = gcc

CFLAGS = -Wall -g

SRCS = main.c arff.c

OBJS = $(SRCS:.c=.o)

EXEC = program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
