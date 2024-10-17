#include <stdio.h>  // For input/output functions like printf, scanf
#include <stdlib.h> // For memory allocation functions like malloc, free, and exit

// Function to initialize a dynamic array
// Parameters:
// - a: a pointer to a long integer array
// - n: a pointer to an integer representing the size of the array
void ini(long* a, int* n){
    // Allocate memory for an array of 'n' long integers
    a = malloc(sizeof(long) * (*n));    
    // If memory allocation fails, exit the program
    if (!a) exit(1);
}

// Function to fill the array with values
// Each element is set to 100 * index
// Parameters:
// - a: a pointer to the long integer array
// - b: a pointer to an integer (size of the array)
void fill(long* a, int* b){
    // Loop through the array and set each element to 100 * index
    for (int i = 0; i < *b; i++){
        a[i] = 100 * i;
    }
}

// Function to print the array contents
// Parameters:
// - a: a pointer to the long integer array
// - b: a pointer to an integer (size of the array)
void imprime(long* a, int* b){
    // Loop through the array and print the index and value at that index
    for (int i = 0; i < *b; i++){
        printf("%d: %ld \n", i, a[i]);
    }
}

// Function to free the dynamically allocated memory for the array
// Parameters:
// - a: a pointer to the long integer array to be freed
void libera(long* a){
    free(a);  // Free the memory allocated for the array
    a = NULL; // Set the pointer to NULL to avoid dangling pointers
}

int main(){
    // Dynamically allocate memory for an integer 'n' (size of the array)
    int* n = malloc(sizeof(int*));
    // If memory allocation fails, exit the program
    if (!n) exit(1); 
    
    // Ask the user to input the size of the array
    printf("entre o tamanho do vetor: "); 
    scanf("%d", &*n);  // Store the input in 'n'

    // Dynamically allocate memory for an array of 'n' long integers
    long* v = malloc(sizeof(long) * (*n));

    // Initialize the array with the ini function
    ini(v, n); 

    // Fill the array with values using the fill function
    fill(v, n); 

    // Print the contents of the array using the imprime function
    imprime(v, n); 
    
    // Free the memory allocated for 'n' and set the pointer to NULL
    free(n);
    n = NULL;

    // Free the memory allocated for the array 'v' and set it to NULL
    libera(v);

    // Return 0 to indicate successful program completion
    return 0; 
}
