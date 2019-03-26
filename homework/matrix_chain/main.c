#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain.h"
#define MAX_ELEM_VALUE 250

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols)
{
   for (size_t i=0; i< A_rows; i++) {
     for (size_t j=0; j< A_cols; j++) {
   	   A[i][j]=rand()%(2*MAX_ELEM_VALUE)-MAX_ELEM_VALUE; //between (-MAXVALUE+1,MAXVALUE-1)
     }
   }
}

float **allocate_matrix(const size_t rows,
                        const size_t cols)
{
   float **A=(float **)malloc(sizeof(float *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(float *)malloc(sizeof(float)*cols);
   }

   return A;
}

void deallocate_matrix_fl(float **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}


int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols)
{
  if (A_cols != B_rows) {
     return -1;
  }

  // for all rows in A
  for (size_t i=0; i<A_rows; i++) {

     // for all cols in B
     for (size_t j=0; j<B_cols; j++) {

       // reset C[i][j]
       C[i][j] = 0.0;

       // sum all the element mults
       for (size_t k=0; k<A_cols; k++) {
        C[i][j] += (A[i][k]*B[k][j]);
       }
     }
  }

  return 0;
}


double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}


void copy_matrix(float **A, float**B, int Ar, int Ac){
  for(size_t i = 0; i < Ar; i++)
  {
    for(size_t j = 0; j < Ac; j++)
    {
      B[i][j]=A[i][j];
    }
    
  }
  
}


int main()
{
    int n=4; //number of matrices
    int* P= (int*)malloc(sizeof(int)*(n+1));

    //creating ad filling matrixes
    P[0]=3;
    P[1]=5;
    P[2]=10;
    P[3]=2;
    P[4]=3;
    

    float*** A=(float***)malloc(n*sizeof(float**));
    for(size_t i = 0; i < n; i++)
    {
        A[i]= allocate_matrix(P[i],P[i+1]); //creates vector of matrixes
        randomly_fill_matrix(A[i],P[i],P[i+1]); //fill each matrix
    }
    //matrixes for partial results
    float **C=allocate_matrix(P[0],P[1]);
    copy_matrix(A[0],C,P[0],P[1]);

    //time stuff
    struct timespec b_time, e_time;
    double time=0.0;
    
    //naive ordered matrix_multiplication
    for(size_t i = 0; i < n-1; i++)
    {
        float **D=allocate_matrix(P[0],P[i+2]);  //allocate new D
        


        clock_gettime(CLOCK_REALTIME, &b_time);
        naive_matrix_mult(D,C,A[i+1],P[0],P[i+1],P[i+1],P[i+2]);
        clock_gettime(CLOCK_REALTIME, &e_time);

        time+=get_execution_time(b_time, e_time);

        
        
        deallocate_matrix_fl(C,P[0]); //free partial results
        float **C=allocate_matrix(P[0],P[i+2]);
        copy_matrix(D,C,P[0],P[i+2]); //prepare new partial results

        deallocate_matrix_fl(D,P[0]);
    }

    deallocate_matrix_fl(C,P[n-1]);    

    printf("naive time\tnew time\n");
    printf("%lf\t", time);

    time=0;
    //
    //to be implemented the exploitation of parenthetization
    //
    //
    //
    //
    //
    //
    printf("%lf\n",time);
    int** s=matrixchain(P,n);

/*
    for(int i = 0; i < (n-1); i++)
    {
        for(int j = 0; j < n-1; j++)
        {
            printf("%d ", s[i][j]);
        }
    printf("\n");    
    }
//checked it give wanted results for both s and m
*/ 





    //deallocating everything
    for(size_t i = 0; i < n; i++)
    {
        deallocate_matrix_fl(A[i],P[i]);
    }
    free(A);

    //deallocate s
    for (size_t i=0; i<n-1; i++) {
    free(s[i]);
    }

    free(s);
    free(P);
    return 0;
}