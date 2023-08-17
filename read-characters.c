#include <stdio.h>
#include <stdlib.h>

#define size 20

int main(){
    FILE* file; 
    char value; 

    file = fopen("arq.txt", "r"); 

    if (!file)
    {
        perror("unable to access file");
        return 1; 
    }
    
    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%c", &value); 
        printf("%d: %c\n", i, value); 
    }
    
    fclose(file); 

    return 0; 
}