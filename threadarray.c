//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



//*********************************************************
//
// Function Prototypes
//
//*********************************************************
void * thread_main(void *data);

//*********************************************************
//
// Main Function
//
//*********************************************************

int main (int argc, char *argv[]){

    //checking if right number of arguments were passed in
    if(argc != 2){
        fprintf(stderr, "Enter proper number of arguments.\n");
    }

    int entry = atoi(argv[1]); //convert number user entered from string to int
    
    pthread_t tids[entry]; 	//thread IDs created according to user specified amount
   
    //so long as we have threads to create,
    for(long int ii=1; ii <=entry; ii++){
        pthread_create(&tids[ii], NULL, thread_main, (void*)ii);
    }

    //cleaning up threads
    for (int ii = 1; ii <=entry; ii++){
        pthread_join(tids[ii], NULL);
    }
 
    return(0);
}

/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////

/*
This function to processes to display hellos and his according to the number imputted by the user
If the thread number is an even, it will say Hi. If the thread number is odd, it will say Hello.


Locals:
long int    ii    data entered by user casted so we can work with it

The function does not return anything.
*/

void * thread_main(void *data){
    
    //converting data into long int
    long int ii = (long int)data;
    
    //evens say hi
     if((ii%2) == 0){
        printf("Thread %ld says Hi\n", ii);
    }
    //odds say hello
    else{
        printf("Thread %ld says Hello\n", ii);
    }

    return NULL;
}
