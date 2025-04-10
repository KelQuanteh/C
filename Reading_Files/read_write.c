#include <stdio.h>

int main(){

    FILE* arq; 

    char byte_escrito, byte_lido; 

    arq = fopen("arquivo.txt", "r+"); 

    if (!arq){
        perror("unable to read file\n");
        return 1; 
    }
    
    //read char from file
    byte_lido = fgetc(arq); 

    printf("O byte lido é: %c\n", byte_lido);

    //insert char into file
    byte_escrito = 'A';
    fputc(byte_escrito, arq);  

    fclose(arq); 

    return 0; 
}