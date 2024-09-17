//*********************************************************
// Playing with threads: thread array
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

///////////////////
// Global Variables
///////////////////
int gargc;
char ** gargv;
int gindex;
// char *ptr;


//thread functions 
void * t_number(void *data);
void * t_upper(void *data);
void * t_lower(void *data);
void * t_other(void *data);

//main function
int main (int argc, char *argv[]){

    //initializing the Globals
    gargc = argc;
    gargv = argv;
    gindex = 1;

    if(argc == 1){
        printf("Error: Need to pass in a string.\n");
    }
    
    //creating tIDs 
    pthread_t tidup, tidlow, tidother, tidnum;

    pthread_create(&tidup, NULL, t_upper, NULL);
    pthread_create(&tidlow, NULL, t_lower, NULL);
    pthread_create(&tidother, NULL, t_other, NULL);
    pthread_create(&tidnum, NULL, t_number, NULL);

    // printf("threads created\n");

    pthread_join(tidup, NULL);
    pthread_join(tidlow, NULL);
    pthread_join(tidother, NULL);
    pthread_join(tidnum, NULL);

    // printf("threads joined.\n");

    return(0);
}

/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////

/*
FINISHHHHHH 



This function to processes the types of characters a user can input
If the user inputted a built-in command, it will be executed and the function will return true.
Else, the function returns false.
bool True if a builtin command was entered, false if otherwise.
Parameters:
toks        char pointer    tokenized user input array
num_toks    int             number of tokens entered by user
*/

void * t_number(void *data){
    double num_token;
    char *ptr;
    //need to make sure entire token is a number, not just the first character
    while(gindex < gargc){
        num_token = strtod(gargv[gindex], &ptr);
            if(ptr != gargv[gindex] && *ptr == '\0'){
                printf("NUMBER:\t%s\n", gargv[gindex]);
                gindex++;

            }
            else{
                sched_yield();
            }
    }
}

void * t_upper(void *data){
    while(gindex < gargc){
        //while the first chracter is a letter
        if(isupper(gargv[gindex][0])){
            printf("UPPER:\t%s \n", gargv[gindex]);
            gindex++;
        }
        else{
            sched_yield();
        }
    }
}

void * t_lower(void *data){
    while(gindex < gargc){
        //while the first chracter is a lowercase
        if(islower(gargv[gindex][0])){
            printf("LOWER:\t%s \n", gargv[gindex]);
            gindex++;
        }
        else{
            sched_yield();
        }
    }
}

void * t_other(void *data){
     double num_token;
    char *ptr;
    while(gindex < gargc){
        num_token = strtod(gargv[gindex], &ptr);
        if(!(islower(gargv[gindex][0]) || isupper(gargv[gindex][0]) ||(ptr != gargv[gindex] && *ptr == '\0' ))){
            printf("OTHER:\t%s \n", gargv[gindex]);
            gindex++;

        }
        else{
            sched_yield();
        }

    }
}
