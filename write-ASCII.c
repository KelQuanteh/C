#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* file; 
    unsigned char c; 

    file = fopen ("arq.txt", "w+"); 

    if (!file)
    {
        perror("Error in accessing file"); 
        return 1; 
    }
    
    fputs("ASCII Characters:", file); 

    for (c = 32; c < 128; c++)
    {
        fputc(c, file); 
        fputc(' ', file); 
    }
    
    fputc('\n', file); 

    fclose(file); 

    return 0; 
}