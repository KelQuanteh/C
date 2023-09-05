#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "mad.h"

int opt; 

int main(int argc, char** argv){
    while ((opt = getopt(argc, argv, "a::s::m::d::")) != -1)
    {
        switch (opt)
        {
        case 'a':
            printf("a soma é %d \n", soma(atoi(argv[2]), atoi(argv[3])));
            break;
        case 'm':
            printf("o produto é %d \n", mult(atoi(argv[2]), atoi(argv[3])));
            break;
        case 's': 
            printf("o restante é %d \n", sub(atoi(argv[2]), atoi(argv[3])));
            break;
        case 'd':
            printf("o quotiente é %d \n", divi(atof(argv[2]), atof(argv[3])));
            break;
        default:
            fprintf(stderr, "Usage: %s [-a, -s, -m, -d] num1 num2 \n", argv[0]);
            return 1;
        }
    }    

    return 0; 
}