#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char** argv) {
    int opt;
    int arg;

    while ((opt = getopt(argc, argv, "an:")) != -1) {
        switch (opt) {
            case 'a':
                for (int i = 0; i < argc; i++)
                    printf("%s \n", argv[i]);
                break;
            case 'n':
                arg = atoi(optarg);
                for (int i = 0; i < arg; i++)
                    printf("%s \n", argv[i]);
                break;
            default:
                fprintf(stderr, "Usage: %s [-a, -n value] <others> \n", argv[0]);
                return 1;
        }
    }

    return 0;
}

