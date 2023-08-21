#include <stdio.h>
#include <stdlib.h>

#define tam 1024

int main(){
    FILE* file1;
    FILE* file2; 

    char line[tam + 1]; 

    file1 = fopen("addition-table.txt", "r"); 
    if (!file1)
    {
        perror("unable to access file"); 
        return 1; 
    }

    file2 = fopen("addition-table(copy).txt", "w"); 
    if (!file2)
    {
        perror("unable to access file"); 
        return 1; 
    }
    
    while (fgets(line, tam, file1))
    {
        fputs(line, file2); 
    }
    
    fclose(file1); 
    fclose(file2); 

    return 0;
}