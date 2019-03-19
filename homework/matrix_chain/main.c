#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain.h"


double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}


int main()
{
    int n=4; //number of matrices
    int* P= (int*)malloc(sizeof(int)*(n+1));

    P[0]=3;
    P[1]=5;
    P[2]=10;
    P[3]=2;
    P[4]=3;
    
    int** m=matrixchain(P,n);
    for(int i = 0; i < (n); i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ", m[i][j]);
        }
    printf("\n");    
    }
    
    deallocate_matrix(m,n);
    return 0;
}