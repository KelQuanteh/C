// game.c
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include <allegro5/allegro_image.h>


// Implementações das funções
ALLEGRO_BITMAP* load_bitmap(const char* filename) {
    ALLEGRO_BITMAP* bitmap = al_load_bitmap(filename);
    if (!bitmap) {
        perror("Não foi possível abrir o arquivo");
        fprintf(stderr, "Nome do arquivo: %s\n", filename);
        exit(1);
    }
    return bitmap;
}

ALLEGRO_SAMPLE* load_sample(const char* filename) {
    ALLEGRO_SAMPLE* song = al_load_sample(filename);
    if (!song) {
        perror("Não foi possível abrir o arquivo");
        fprintf(stderr, "Nome do arquivo: %s\n", filename);
        exit(1);
    }
    return song;
}

int collide(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh) {
    return Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bh;
}



