all:	space_enemies

space_enemies:	A3.o	space.o	enemy.o
	gcc	-Wall	A3.o	space.o	enemy.o	-o	space_enemies

A3.o:	A3.c	enemy.h	enemy.o
	gcc	-Wall	-c	A3.c

space.o:	space.c	space.h
	gcc	-Wall	-c	space.c

enemy.o:	enemy.c	enemy.h	space.h
	gcc	-Wall	-c	enemy.c

clean:
	rm	-f	*.o	space_enemies