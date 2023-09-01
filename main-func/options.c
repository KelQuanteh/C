#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int a = 0;      // Flag to indicate if option 'a' was provided
    int b = 0;      // Flag to indicate if option 'b' was provided
    char* c = NULL; // Variable to store the argument provided with option 'c'
    int option;     // Variable to store the current option being processed

    // Loop through command-line options using getopt
    while ((option = getopt(argc, argv, "abc:")) != -1) {
        switch (option) {
            case 'a':
                a = 1; // Set the 'a' flag to 1 when option 'a' is provided
                break;
            case 'b':
                b = 1; // Set the 'b' flag to 1 when option 'b' is provided
                break;
            case 'c':
                c = optarg; // Store the argument provided with option 'c' in the 'c' variable
                break;
            default:
                // Print an error message for invalid or missing options
                fprintf(stderr, "Usage: %s [-a, -b, -c:argument]\n", argv[0]);
        }
    }

    // Print the values of the flags and the 'c' variable
    printf("Flag a = %d, Flag b = %d, Flag c = %s\n", a, b, c);

    return 0;
}
 
