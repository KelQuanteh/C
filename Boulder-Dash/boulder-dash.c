#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define size 1024
#define arquivo "mapa.txt"

int main(){
    FILE* file;
    file = fopen(arquivo, "r");

    if(!file){
        perror("unable to open file: ");
        return 1;
    }

    char line[size + 1];
    char mat[size][size];

    int i= 0; 

    fgets(line, size, file);

    while (!feof(file)){
        int tam = strlen(line);

        for (int j = 0; j <= tam; j++)
        {
            mat[i][j] = line[j];
        }
        
        printf("%d: %s\n", i, mat[i]);

        fgets(line, size, file);
        i++;
    }
    
    fclose(file);
    
    return 0; 
}