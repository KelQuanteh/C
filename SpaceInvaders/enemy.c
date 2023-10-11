#include <stdlib.h>
#include <stdio.h>

#include "enemy.h"

// Função para criar uma lista de tiros
shot_sentinel* create_shotlist(void) {
    shot_sentinel* list = (shot_sentinel*)malloc(sizeof(shot_sentinel));
    if (list == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para shot_sentinel\n");
        return NULL;
    }
    list->first = NULL;
    list->last = NULL;
    return list;
}

// Função para remover um tiro da lista
shot* remove_shot(shot* current, shot* previous, shot_sentinel* list) {
    if (current == NULL) {
        fprintf(stderr, "Erro: Tentativa de remover um tiro NULL\n");
        return NULL;
    }

    if (current == list->first) {
        list->first = current->next;
    } else {
        if (previous != NULL) {
            previous->next = current->next;
        }
    }

    if (current == list->last) {
        list->last = previous;
    }

    shot* next_shot = current->next;
    free(current);
    return next_shot;
}

// Função para limpar todos os tiros da lista
void clean_shots(shot_sentinel* list) {
    shot* current = list->first;
    shot* previous = NULL;
    
    while (current != NULL) {
        current = remove_shot(current, previous, list);
    }
}

// Função para adicionar um novo tiro à lista
shot_sentinel* straight_shoot(space* board, shot_sentinel* list, enemy* shooter) {
    if (shooter == NULL || list == NULL) {
        fprintf(stderr, "Erro: Parâmetros inválidos em straight_shoot\n");
        return list;
    }

    shot* new_shot = (shot*)malloc(sizeof(shot));
    if (new_shot == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para um novo tiro\n");
        return list;
    }

    new_shot->position_x = shooter->position_x;
    new_shot->position_y = shooter->position_y;
    new_shot->trajectory = 0;
    new_shot->next = NULL;

    if (list->last == NULL) {
        list->first = new_shot;
        list->last = new_shot;
    } else {
        list->last->next = new_shot;
        list->last = new_shot;
    }

    return list;
}

// Função para atualizar a posição dos tiros na lista
void update_shots(space* board, shot_sentinel* list) {
    shot* current = list->first;
    shot* prev = NULL;

    while (current != NULL) {
        current->position_y++;

        if (current->position_y > board->max_y) {
            if (prev == NULL) {
                list->first = current->next;
                if (list->first == NULL) {
                    list->last = NULL;
                }
            } else {
                prev->next = current->next;
                if (current == list->last) {
                    list->last = prev;
                }
            }

            shot* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Função para adicionar um inimigo à posição especificada no tabuleiro
int add_enemy(space* board, int position_y, int position_x) {
    if (position_y < 0 || position_y > board->max_y || position_x < 0 || position_x > board->max_x) {
        return 0; // Retorna 0 em caso de posição inválida
    }

    enemy* new_enemy = malloc(sizeof(enemy));

    if (new_enemy == NULL) {
        return 0; // Retorna 0 em caso de falha na alocação de memória
    }

    new_enemy->position_x = position_x;
    new_enemy->position_y = position_y;

    board->map[position_y][position_x].entity = new_enemy;
    board->map[position_y][position_x].type = ENEMY;

    return 1; // Retorna 1 em caso de sucesso
}

// Função para remover um inimigo da posição especificada no tabuleiro
int remove_enemy(space* board, int position_y, int position_x) {
    if (position_y < 0 || position_y > board->max_y || position_x < 0 || position_x > board->max_x) {
        return 0; // Retorna 0 em caso de posição inválida
    }

    enemy* enemy_to_remove = board->map[position_y][position_x].entity;

    if (enemy_to_remove == NULL) {
        return 0; // Retorna 0 se não houver inimigo para remover
    }

    free(enemy_to_remove);
    board->map[position_y][position_x].entity = NULL;

    return 1; // Retorna 1 em caso de sucesso na remoção do inimigo
}
