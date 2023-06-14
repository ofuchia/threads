//*********************************************************
// Ofuchinyelu Akpom
// Operating Systems
// Playing with threads: pthread calculator
// March 5, 2023
// Instructor: Dr. Scherger
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <cmath>

//*********************************************************
//
// Function Prototypes
//
//*********************************************************
void * thread_min(void *data);
void * thread_max(void *data);
void * thread_mean(void *data);
void * thread_median(void *data);
void * thread_mode(void *data);
void * thread_stdev(void *data);
int sort(const void *one, const void* two);

//*********************************************************
//
// Main Function
//
//*********************************************************
int main (int argc, char *argv[]){

    //creating a local variable called size to hold the size of argc+1
    int size = argc + 1;
 
    //checking number of arguments
    if(argc == 1){
        fprintf(stderr, "Must include integers for calcualting.\n");
    }

    // create a int num array - size is argc+1
    int num[size];
    //storing the command line size into the first pocket for easy access
    num[0] = argc;

    //converting the input from terminal into integers
    for(int dd= 1; dd < argc; dd++){
        num[dd] = atoi(argv[dd]);
    }


  
    //creating one tid that all the treads will use
    pthread_t tid;

    //creating and joining threads after they've done their jobs
    pthread_create(&tid, NULL, thread_min, (void*)num);
    pthread_join(tid, NULL);
    
    pthread_create(&tid, NULL, thread_max, (void*)num);
    pthread_join(tid, NULL);
    
    pthread_create(&tid, NULL, thread_mean, (void*)num);
    pthread_join(tid, NULL);
    
    pthread_create(&tid, NULL, thread_median, (void*)num);
    pthread_join(tid, NULL);
    
    pthread_create(&tid, NULL, thread_mode, (void*)num);
    pthread_join(tid, NULL);

    pthread_create(&tid, NULL, thread_stdev, (void*)num);
    pthread_join(tid, NULL);
}

/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////
/*
This funciton finds the minimun of the values entered by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int     min         initalized to second entry in array
int     size        storing size of argc


Returns:
Nothing.
*/
void * thread_min(void *data){
    //scan enire array and find the lowest number
    
    //converting data into int* ...or isnt this not needed bc done before storing into array?
    //gotta pass working in 
    int *num = (int *) data;
    int min = num[1];
    int size = num[0];

    //n needs to be the entirety of the working array
    //looping through array and finding min3
    for(int ii = 1; ii < size; ii++){
        if(num[ii] < min){
            min = num[ii];
        }
    }
    //printing out the minimum
    printf("MIN:\t\t%d\n", min);
    return NULL;
}

/*
This funciton finds the maximum value entered by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int         max     initalilly the second entry in the array  
int         size    sizeo f argc


Returns:
Nothing.
*/
void * thread_max(void *data){
    //scan enire array and find the maximum number
    
    //converting data into int*
    //initializing the local variables
    int *num = (int *) data;
    int max = num[1];
    int size = num[0];

    //n needs to be the entirety of the working array
    //looping through array and finding max
    for(int ii = 1; ii < size; ii++){
        if(num[ii] > max){
            max = num[ii];
        }
    }
    //printing out the max
    printf("MAX:\t\t%d\n", max);
    return NULL;
}


/*
This funciton finds the Mean using the numbers entered in by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int     size       size of argc
int     sum        summation of all entered integers
float   ans        final answer; mean


Returns:
Nothing.
*/
void * thread_mean(void *data){
    //calculating mean: add all, divide by num[0] (size)

    //casting data and initializing local variables
    int *num = (int *) data;
    int size = num[0];
    int sum = 0;
    float ans = 0;

    //n needs to be the entirety of the working array
    //looping through array and adding all the numbers
    for(int ii = 1; ii < size; ii++){
        sum += num[ii];
    }   

    ans = (float) sum / (size-1);

    //printing out the mean
    printf("MEAN:\t\t%0.3f\n", ans);
    return NULL;
}

/*
This funciton finds the Median using the numbers entered in by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int     size        size of argc
float   median    final answer; median

Returns:
Nothing.
*/

void * thread_median(void *data){
    //add all, divide by num[0]

    int *num = (int *) data;
    int size = num[0]-1;
    float median = 0;

    //order the array
    qsort(num+1, size, sizeof(int), sort);
    //if even, add the two middles ones and divide by 2
    if(size%2 == 0){
        median = (float) (num[size/2] + num[(size/2) + 1]) / 2;
    }
    //perfect middle
    else{
        median = (float) num[(size/2) + 1];
    }


    printf("MEDIAN:\t\t%0.0f\n", median);
    return NULL;
}

/*
This function compares the values pointed to by one and two and orders them

Parameters:
void*       one    data the pointer points to, coems from user entry
void*       two    data the pointer points to; comes from user entry

Local Variables:
--------------------------------------------
None

Returns:
A postiive integer if one < two and negative if one > two
*/

int sort(const void *one, const void* two){
    return(*(int*)one - *(int*)two);
}

/*
This funciton finds the Mode using the numbers entered in by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int  size    working size
int  mode    initalized to 0
int  most    local highest frequency

Returns:
Nothing.
*/

void * thread_mode(void *data){
    //add all, divide by num[0]

    int *num = (int *) data;
    int size = num[0]-1;
    int mode  = 0;
    int most = 0;
    //order the array
    qsort(num+1, size, sizeof(int), sort);
    //loop through the array, tallying them
    for(int ii = 1; ii <= size; ii++){
        int local = 0;
        for(int j = 1; j <= size; j++){
            if(num[j] == num[ii]){
                local++;
            }
        }
        if(local > most){
            most = local;
            mode = num[ii];
        }

    }

    if(most <= 1){
        printf("MODE:\t\tNO MODE\n");
    }
    else{
        printf("MODE:\t\t%d\n", mode);
    }

    return NULL;
}
/*
This funciton finds the standard deviation using the numbers entered in by the user.
Parameters:
void*       data    data entered in by user

Local Variables:
--------------------------------------------
int size working size
int     sum         summing command line integers
float   mean_ans    calculating the mean
float   total       intemediate total
float   stdev       final answer 


Returns:
Nothing.
*/

void * thread_stdev(void *data){
    int *num = (int *) data;
    int size = num[0]-1;
    int sum = 0;
    float mean_ans = 0;
    float total = 0;
    float stdev = 0;
    //n needs to be the entirety of the working array
    //looping through array and adding all the numbers
    
    //finding the mean
    for(int ii = 1; ii < size; ii++){
        sum += num[ii];
    }   

    mean_ans = (float) sum / (size-1);

    //finding the stdev
    for(int ii=1; ii <=size; ii++){
        total = (float) total + pow(num[ii]- mean_ans, 2);
    }

    stdev = (float) sqrt(total/(size-1));

    printf("STD. DEV:\t%0.3f\n", stdev);
    return NULL;
}
