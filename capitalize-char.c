#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    // Declare file pointers
    FILE* file1;
    FILE* file2; 

    // Open the first file for reading
    file1 = fopen("combine-multiple-reducers.txt", "r");
    if (!file1)
    {
        perror("Unable to read file1"); 
        return 1; // Exit with an error code
    }

    // Open the second file for writing
    file2 = fopen("CAPS.txt", "w");
    if (!file2)
    {
        perror("Unable to read file2"); 
        return 1; // Exit with an error code
    }

    char c = fgetc(file1); // Read the first character from file1
    char cap; // Variable to store the uppercase character
    while (c != EOF) // Loop until the end of file1 is reached
    {
        if (isalpha(c)) // Check if the character is an alphabet letter
            cap = toupper(c); // Convert the character to uppercase
        
        fputc(cap, file2); // Write the uppercase character to file2
        
        c = fgetc(file1); // Read the next character from file1
    }
    
    // Close the opened files
    fclose(file1); 
    fclose(file2); 

    return 0; // Exit indicating success
}
