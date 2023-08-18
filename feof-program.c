#include <stdio.h>
#include <stdlib.h>

#define size 1024

int main(){
    FILE* file; 
    file = fopen("combine-multiple-reducers.txt", "r");

    char line[size + 1]; 

    if (!file)
    {
        perror("Unable to read file"); 
        return 1;
    }
    
    int i = 1; 

    fgets(line, size, file); 
    while (!feof(file))
    {
        printf("%d: %s \n", i, line);
        fgets(line, size, file);  
        i++;
    }
    
    fclose(file);

    return 0; 
}