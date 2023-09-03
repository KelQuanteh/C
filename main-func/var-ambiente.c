#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char** argv) {
    int opt;    // Variable to store the current option
    int arg;    // Variable to store the integer argument for the -n option

    // Use getopt to parse command-line options. The "an:" string specifies
    // that this program accepts options -a (no argument) and -n (requires an argument).
    while ((opt = getopt(argc, argv, "an:")) != -1) {
        switch (opt) {
            case 'a':
                // If the -a option is provided, print all command-line arguments.
                for (int i = 0; i < argc; i++)
                    printf("%s \n", argv[i]);
                break;
            case 'n':
                // If the -n option is provided, convert the optarg to an integer
                // and print the specified number of command-line arguments.
                arg = atoi(optarg);
                for (int i = 0; i < arg; i++)
                    printf("%s \n", argv[i]);
                break;
            default:
                // If an unknown option is provided, print a usage message and exit with an error.
                fprintf(stderr, "Usage: %s [-a, -n value] <others> \n", argv[0]);
                return 1;
        }
    }

    return 0;
}
