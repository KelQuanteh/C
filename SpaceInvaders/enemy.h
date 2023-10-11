#ifndef __ENEMY__
#define __ENEMY__

#include "space.h"

// Definição da estrutura 'shot' que representa um tiro.
typedef struct shot shot;
struct shot{
	int position_x;  // Posição X do tiro.
	int position_y;  // Posição Y do tiro.
	int trajectory;  // Trajetória do tiro (não utilizado neste código).
	shot *next;     // Próximo tiro na lista.
} ;

// Definição da estrutura 'shot_sentinel' que mantém uma lista de tiros.
typedef struct shot_sentinel{
	shot *first;  // Primeiro tiro na lista.
	shot *last;   // Último tiro na lista.
} shot_sentinel;

// Definição da estrutura 'enemy' que representa um inimigo.
typedef struct enemy{
	int position_x;  // Posição X do inimigo.
	int position_y;  // Posição Y do inimigo.
} enemy;

// Funções relacionadas aos tiros (shots).
shot_sentinel* create_shotlist(void); // Cria uma lista de tiros vazia.
void clean_shots(shot_sentinel *list); // Remove todos os tiros da lista.
shot* remove_shot(shot* current, shot* previous, shot_sentinel *list); // Remove um tiro da lista.
shot_sentinel* straight_shoot(space *board, shot_sentinel *list, enemy *shooter); // Realiza um tiro reto.
void update_shots(space *board, shot_sentinel *list); // Atualiza a posição dos tiros.

// Funções relacionadas aos inimigos.
int add_enemy(space *board, int position_y, int position_x); // Adiciona um inimigo à posição especificada.
int remove_enemy(space *board, int position_y, int position_x); // Remove um inimigo da posição especificada.

#endif
