#include <stdio.h>
#include <stdlib.h>

#define size 100

int main(){
    FILE* file; 
    char line[size + 1]; 

    file = fopen("addition-table.txt", "r"); 

    if (!file)
    {
        perror("not able to access file"); 
        return 1; 
    }
    
    for (int i = 0; i < 9; i++)
    {
        fgets(line, size, file); 
        printf("%d %s", i, line);
    }
    
    fclose(file);

    return 0; 
}