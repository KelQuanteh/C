#include <stdio.h>
#include <stdlib.h>

#define tam 100

typedef struct citizen_t
{
    char id[11];
    int habilidade;
    int criminalidade;
} citizen;

int main(){
    FILE* file; 
    citizen pessoa;

    file = fopen ("citizens.bin", "rb"); 

    if (!file)
    {
        perror("error de ler arquivo");
        return 1; 
    }

    int total, cinco; 
    float media = 0.0; 

    while (fread(&pessoa, sizeof(citizen), 1, file) == 1)
    {
        printf("ID: %s \n", pessoa.id);
        printf("Habilidade: %d \n", pessoa.habilidade);
        printf("Criminalidade: %d \n", pessoa.criminalidade);

        printf("<----------------------------------------> \n");

        total++; 
        
        if (pessoa.criminalidade > 5)
            cinco++; 

        media = (media + pessoa.habilidade) / total;
    }
    
    printf("A quantidade total de cidadãos no arquivo é: %d\n", total);
    printf("O número de cidadãos com níveis de criminalidade acima de 5 é: %d\n", cinco);
    printf("A média dos níveis de habilidades em hacking de todos os cidadãosé: %f\n", media);

    fclose(file);

    return 0; 
}