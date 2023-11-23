# Makefile
CC = gcc
CFLAGS = -Wall -Wextra	-g
LIBS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

space-invaders: main.c game.c
	$(CC) $(CFLAGS) main.c game.c -o space-invaders $(LIBS)

clean:
	rm -f space-invaders

purge: clean
	rm -f *.o
