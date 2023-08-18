#include <stdio.h>
#include <stdlib.h>

int main(){
    // Declare a pointer to a FILE structure
    FILE* file; 
    // Open the file "combine-multiple-reducers.txt" in read mode ("r")
    file = fopen("combine-multiple-reducers.txt", "r");

    // Check if the file was successfully opened
    if (!file)
    {
        perror("Unable to read file"); // Print an error message with the cause of the failure
        return 1; // Exit the program with a non-zero status indicating an error
    }
    
    char c = fgetc(file); // Read the first character from the file
    long count = 1; // Initialize a counter to keep track of characters (starting at 1 because of the first character)

    // Loop through the file until the end of the file (EOF) is reached
    while (c != EOF)
    {
        c = fgetc(file); // Read the next character from the file
        count++; // Increment the character count
    }
    
    // Print the total number of characters counted
    printf("Total number of characters: %ld\n", count); 

    // Close the file
    fclose(file); 

    return 0; // Exit the program with a status of 0 to indicate successful execution
}
