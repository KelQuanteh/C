//tiro.h
#ifndef TIRO_H
#define TIRO_H

#define VEL 15
#define N_TIROS 1
#define SCREEN_X 1290
#define SCREEN_Y 1050

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

enum ESTADO {ATIVO, NAO_ATIVO};

typedef struct pistol_t{
    int x;
    int y;
    int width; 
    int height; 
    int vel;
    int ativo;
    ALLEGRO_BITMAP* img_pistol;
} pistol;

void pistol_init(pistol *t);

void desenha_pistol(pistol *t);

void trigger(pistol* pistol, int x, int y);

void aumenta_vel(pistol *t);

#endif