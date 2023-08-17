#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* file; 

    file = fopen("addition-table.txt", "w+"); 

    if (!file)
    {
        perror("error in opening/creating file"); 
        return 1; 
    }
    
    fputs("Addition Table: ", file); 
    fputc('\n', file); 

    fprintf(file, "     "); 

    for (int i = 0; i <= 5; i++)
    {
        fprintf(file, "%3d", i);
    }

    fputc('\n', file); 
    
    for (int i = 0; i <= 5 ; i++)
    {
        fprintf(file, "%3d |", i); 
        for (int j = 0; j <= 5; j++)
            fprintf(file, "%3d", i + j);
        fputc('\n', file);    
    }
    
    fclose(file);

    return 0; 
}