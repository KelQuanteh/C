#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(){
    printf("This is a thread\n"); 
    sleep(5); 
    printf("Thread ended\n"); 
}

int main(){

    //create threads using pthread+t struct
    pthread_t t1, t2; 

    //initialize threads
    if (pthread_create(&t1, NULL, &routine, NULL)){
        perror("Unable to create thread\n"); 
        exit(1); 
    }
    
    if (pthread_create(&t2, NULL, &routine, NULL)){
        perror("Unable to create thread\n"); 
        exit(1); 
    }

    //get threads
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL);

    return 0; 
}