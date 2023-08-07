#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

typedef struct data_t
{
    int dia; 
    int mes; 
    int ano; 
} data_t;

typedef struct hora_t
{
    int hora; 
    int minuto; 
    int segundo; 
} hora_t;

typedef struct dataHora_t 
{
    data_t datas; 
    hora_t horarios;
} dataHora_t;

void le_data(data_t* d){
    printf("entre o dia, mes e ano da data: "); 
    scanf("%d %d %d", &d->dia, &d->mes, &d->ano); 
}

void le_hora(hora_t* h){
    printf("entre a hora, minuto e segundo do horario: "); 
    scanf("%d %d %d", &h->hora, &h->minuto, &h->segundo); 
}

void le_dataHora(dataHora_t* dH){
    le_data(&dH->datas); 
    le_hora(&dH->horarios); 
}

void esc_data(data_t d){
    printf("a data e: %d/%d/%d \n", d.dia, d.mes, d.ano); 
}

void esc_hora(hora_t h){
    printf("a hora e: %d:%d:%d \n", h.hora, h.minuto, h.segundo); 
}

void esc_dataHora(dataHora_t dH){
    esc_data(dH.datas); 
    esc_hora(dH.horarios); 
}

int diasDoMes(int d) {
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return dias[d - 1];
}

int dataDias(data_t d){
    int dias = 0;  

    for (int i = 0; i < d.mes - 1; i++) {
        dias += diasDoMes(i + 1);
    }
    dias += d.dia - 1;
    return dias; 
}

int main(){
    dataHora_t dh;
    le_dataHora(&dh);
    esc_dataHora(dh);

    int days = dataDias(dh.datas);
    printf("Number of days since 1st January: %d\n", days);

    return 0; 
}
