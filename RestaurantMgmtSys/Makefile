CFLAGS	=	-Wall	-g	-std=c99

all:
	gcc $(FLAG) -c libpilha.c
	gcc $(FLAG) -c libfila.c
	gcc $(FLAG) -c liblista.c
	gcc $(FLAG) -c extra.c
	gcc $(FLAG) -c ru_na_pandemia.c
	gcc libpilha.o libfila.o liblista.o extra.o	ru_na_pandemia.o -o ru_na_pandemia

#remove arquivos temporarios
clean:
	rm -f *.o *.gch ru_na_pandemia
