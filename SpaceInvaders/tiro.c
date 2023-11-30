//tiro.c
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "tiro.h"

//Inicialize a pistola
void pistol_init(pistol *t)
{
    t->ativo = NAO_ATIVO;
    t->x = 0;
    t->y = 0;
    
    t->img_pistol = al_load_bitmap("tiroA.png");
    t->vel = VEL;

    if( t->img_pistol == NULL) {
        puts( "Erro ao carregar a imagem do pistol.");
        exit(0);
    }
}

//desenhe as balas
void desenha_pistol(pistol *t)
{
    if (t->ativo == ATIVO)
    {
        al_draw_bitmap(t->img_pistol, t->x, t->y, 0);
        if (t->y > 0 && t->y < SCREEN_Y){
           t->y -= t->vel;
        } else {
          t->ativo = NAO_ATIVO;
        }
    }
}

//atirar
void trigger(pistol* pistol, int x, int y)
{
    if (pistol->ativo == NAO_ATIVO)
    {
        pistol->ativo = ATIVO;
        pistol->x = x;
        pistol->y = y;
        desenha_pistol(pistol);
    }
}

//mova as balas
void aumenta_vel(pistol *t){
    t->vel = t->vel;
}