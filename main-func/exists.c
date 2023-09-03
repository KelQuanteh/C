#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char** argv){
	FILE* arq; 
	arq = fopen(argv[1], "r"); 

	if(arq)
		return 0;
	else
		return 1;
}
