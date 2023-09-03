#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h> 
#include <unistd.h>

int val; 

int main(int argc, char** argv){
	int count = 0;

	for(int i = 1; i < argc; i++){
		if(argv[i][0] == '-')
			count++;
	}
	
	val = count;
	
	return (val); 
}
