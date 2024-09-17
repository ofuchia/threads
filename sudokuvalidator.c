//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include<stdbool.h>

//function prototypes
void *t_sudoku(void *argument);

/////////////////////////////////////////////
//Global Variables
////////////////////////////////////////////

bool validate[27];  //creating the validating array
int sudoku[9][9];   //the actual game of sudoku
FILE *fp;

// structure for passing data to threads
typedef struct{
    int row;
    int col;
} Parameters;

//*********************************************************
//
// Main Function
//
//*********************************************************
int main(int argc, char *argv[]){
    
    //argument check
    if(argc == 1){
        fprintf(stderr, "Must include a sudoku file to validate.\n");
        exit(1);
    }

    // variable declarations
    Parameters *data;
    int t_index = 18;
    //creating our 27 tids
    pthread_t tid[27];
    
    
    //opening the file to read
    FILE *fp = fopen(argv[1], "r");
   
    //checking if there's trouble reading from file
    if (fp == NULL){
        fprintf(stderr, "Error, trouble opening file.\n");
        exit(1);
    }

    //populating the sudoku area from the file
    for(int i =0; i<9; i++){
        for(int j=0; j < 9; j++){
            //scanning from the in-file and converting it into an integer
           if ((fscanf(fp, "%d", &sudoku[i][j])) != 1){
            fprintf(stderr, "Error.\n");
            exit(1);
           } 
        }
    }
    //closing the file
    fclose(fp);

    //looping through the columns
    for(int d = 0; d < 9; d++){
        data = (Parameters *) malloc(sizeof(Parameters));
        //where it will start validating
        data->row = 0;
        data->col = d;
        //creating a thread to handle that work; first 9 threads go to columns
        pthread_create(&tid[d], NULL, t_sudoku, (void*)data);
    }

    //looping through the rows
    for(int d = 0; d < 9; d++){
        data = (Parameters *) malloc(sizeof(Parameters));
        //where it will start validating
        data->row = d;
        data->col = 0;
        //creating a thread to handle that work; second set of 9 threads go to rows
        pthread_create(&tid[9+d], NULL, t_sudoku, (void*)data);
    }

    //moving by squares
    for(int ii = 0; ii <9; ii+=3){
        for(int jj= 0; jj <9; jj+=3){
            data = (Parameters *) malloc(sizeof(Parameters));
            data->row = ii;
            data->col = jj;
            //creating a thread to handle that work
            pthread_create(&tid[t_index], NULL, t_sudoku, (void*)data);
            t_index++;
        }
    }

    //cleaning up the tids
    for(int i = 0; i < 27; i++){
        pthread_join(tid[i], NULL);
    }

    //checking the validate array to see if the solution was proper or not
    for(int d = 0; d < 27; d++){
        if(validate[d] == 0){
            //sudoku was not a valid solution
            printf("False.\n");
            return 0;
        } 

    }
    //solution is valid
    printf("True.\n");
    return 0;

    free(data);
}


/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////

/*
This function to processes the sudoku file inputted by the user.
It will cehck that the rows, columns, and squares are proper solutions (that is, contain unique digits) 
and set the validate and seen array flags to indicate if the digit has been seen before or if the solution in that row/column/square is valid

Parameters:
void*       argument    positions passed in from the loops in main

Local Variables:
--------------------------------------------
int     row     row we're at; from main
int     column      column we're at; from main
int[]   seen       an array that stores the digit we've encountered as we loop       
int     startColumn  where to start in cols when calculating blocks
int     startRow      where to start in rows when calcualting blocks
int     columnSquare    where we are within the big sudoku
int     rowSqaure     where we are within the big sudoku


Returns:
Nothing.

*/

void *t_sudoku(void *argument){
    Parameters *data = (Parameters *)argument;
    int row = data -> row;
    int column = data -> col;
    int seen[9];

    //if we are not at the end of our sudoku game
    if(row < 9 && column < 9){
      

//---------------------------COLS------------------------------
        //checking the enteries of the column we're fixed at
        for(int i = 0; i < 9; i++){
            int digit = sudoku[i][column];
            //if the number is invalid 
            if(digit < 1 || digit > 9 || seen[digit-1]){
                //setting that digit's validation in sudoku to false.
                validate[column] = 0;
                //leave thread bc not correct solution
                pthread_exit(NULL);
            }
            //marking that we have seen that digit
            seen[digit-1] =1;
        }
        //stating that the entire columnn is valid
        validate[column] = 1;

        //clearing our seen array so we can track the digits for other computations.
        for(int i = 0; i < 9; i++){
            seen[i] = 0;
        }

//------------------ROWS---------------------------------------------
        //checking the enteries of the row we're fixed at
        for(int i = 0; i <9; i++){
            int digit = sudoku[row][i];
            //if the number is invalid 
            if(digit < 1 || digit > 9 || seen[digit-1]){
                //setting that digits validation in sudoku to false.
                validate[9+row] = 0;
                //leave thread bc not correct solution
                pthread_exit(NULL);
            }
            //marking that we have seen that digit
            seen[digit-1] =1;
        }
        //stating that the entire row is valid
        validate[9+row] = 1;
        
        //clearing our seen array so we can track the digits for other computations.
        for(int i = 0; i <9; i++){
            seen[i] = 0;
    }
        
//------------------------checking squares----------------
        
        //local variables
        int rowSquare = row/3;
        int columnSquare = column/3;
        int startRow = rowSquare *3;
        int startColumn = columnSquare * 3;

        //moving through sudoku by blocks of 3
        for(int d = startRow; d < (startRow+3); d++){
            for(int j = startColumn; j < startColumn +3; j++){
            int digit = sudoku[d][j];
            //if the number is invalid 
            if(digit < 1 || digit > 9 || seen[digit-1]){
                //setting that digit's validation in sudoku to false.
                validate[18 + rowSquare *3 + columnSquare] = 0;
                //leave thread bc not correct solution
                pthread_exit(NULL);
            }
            //marking that we have seen that digit
            seen[digit-1] =1;
            }
        }
        //stating that the entire square is valid
        validate[18 + rowSquare *3 + columnSquare] = 1;


    }
    pthread_exit(NULL);
}
