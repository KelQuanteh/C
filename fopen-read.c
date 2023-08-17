#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* arq;

    arq = fopen("arq.txt", "r"); 

    if (!arq){
        perror("Error in opening archive");
        return 1;
    }
    
    fclose(arq);

    return 0;
}