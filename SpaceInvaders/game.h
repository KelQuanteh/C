// game.h
#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#define SCREEN_X 1290
#define SCREEN_Y 1050
#define PLAYER_WIDTH 100

// Definição das estruturas de dados
typedef struct {
    int x;
    int y;
    int height;
    int width;
} alien[10][7];

typedef struct {
    int x;
    int y;
    int height;
    int width;
} nave;

typedef struct {
    int x;
    int y;
    int height;
    int width;
} obj[3];

typedef struct {
    int count;
} hit[3];

typedef struct {
    int x;
    int y;
    int height;
    int width;
} disco;

typedef struct {
    int x;
    int y;
    int height;
    int width;
} a_pistol[2];

// Declarações das funções
ALLEGRO_BITMAP* load_bitmap(const char* filename);
ALLEGRO_SAMPLE* load_sample(const char* filename);
int collide(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);

#endif // GAME_H
