#include <stdio.h>

int main(int argc, char** argv, char** envp){
	int i; 

	printf("O numero de argumentos säo: %d \n", argc);

	for(i= 0; i< argc; i++){
		printf("arg{%d) : %s \n", i, argv[i]);
	}

	return 0;
}
