#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* file;

    file = fopen("arq.txt", "w+");

    if (!file)
    {
        perror("error in accessing file");
        return 1;
    }
    
    fclose(file);

    return 0; 
}