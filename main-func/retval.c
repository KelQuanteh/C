#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int val; // Global variable to store the count of command-line options

int main(int argc, char** argv) {
    int count = 0; // Local variable to store the count of command-line options

    // Loop through the command-line arguments starting from the second argument (argv[1])
    for (int i = 1; i < argc; i++) {
        // Check if the argument starts with a hyphen '-' indicating it's an option
        if (argv[i][0] == '-')
            count++; // Increment the count for each option encountered
    }

    val = count; // Store the total count of options in the global variable 'val'

    return val; // Return the count of options as the exit status of the program
}
