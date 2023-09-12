CFLAGS	=	-Wall	-g
objs	=	hello.o	escreva.o
all:	hello	
hello:	$(objs)
hello.o:	hello.c	escreva.h
escreva.o: escreva.c	escreva.h

clean:
	-rm	-f	$(objs)	*˜

purge:	clean
	-rm	-f	hello
