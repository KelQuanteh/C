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

    char line[size + 1];  // Buffer to store a line read from the file
    char mat[size][size]; // 2D array/matrix to store the contents of the file

    int i = 0; 

    fgets(line, size, file); // Read the first line from the file into the line buffer

    while (!feof(file)){ // Loop until the end of the file is reached
        int tam = strlen(line); // Determine the length of the line read

        for (int j = 0; j <= tam; j++) {
            mat[i][j] = line[j]; // Copy each character from the line buffer to the matrix
        }
        
        printf("%d: %s\n", i, mat[i]); // Print the row number and its corresponding line

        fgets(line, size, file); // Read the next line from the file into the line buffer
        i++; // Move to the next row in the matrix
    }
    
    fclose(file); // Close the file
    
    return 0; 
}