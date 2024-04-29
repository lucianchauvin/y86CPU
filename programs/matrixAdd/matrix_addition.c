#include <stdio.h>

int main()
{
    //read in dimensions of matrix
    int numrows, numcols;
    scanf("%d", &numrows);
    scanf("%d", &numcols);
    //initialize initialize dimensions of matrices
    int matrix1[numrows][numcols];
    int resultmatrix[numrows][numcols];
    //read input for first matrix
    for(int i = 0; i < numrows; i++) {
        for(int j = 0; j < numcols; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }
    //rad input for second matrix and calculate result
    for(int i = 0; i < numrows; i++) {
        for(int j = 0; j < numcols; j++) {
            scanf("%d", &resultmatrix[i][j]);
            resultmatrix[i][j] += matrix1[i][j];
        }
    }
    
    //optional printing matrix for debugging
    
    for(int i = 0; i < numrows; i++) {
        for(int j = 0; j < numcols; j++) {
            printf("%d ", resultmatrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

/*
sample input:

2 4
5 2 5 1 
6 4 3 6

6 4 7 2
4 5 2 1

*/