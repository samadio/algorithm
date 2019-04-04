#include<stdlib.h>
#include<stdio.h>
#include "side.h"
#include <time.h>
#define MAX_ELEM_VALUE 250
#define CMM(M,row,col) M[row] [col]


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


double using_s(float **res,float ***A,int *P,int **s,int left,int right){
  
  if(left==right){
    copy_matrix(A[left], res,P[left], P[left+1] );
  }

  else{
    int r_par=CMM(s,left,right-1)-1;
    //printf("all fine with r_par: %d ,left: %d ,right: %d ,\n",r_par,left,right);
    //matrixes to store temp results
    float**C_r=allocate_matrix(P[left],P[r_par+1]);
    float**D_l=allocate_matrix(P[r_par+1],P[right+1]);

    using_s(C_r,A,P,s,left,r_par); //recursive call first left then right
    using_s(D_l,A,P,s,r_par+1,right);
    
    naive_matrix_mult(res,C_r,D_l,P[left],P[r_par+1],P[r_par+1],P[right+1]);

    deallocate_matrix_fl(C_r,P[left]);
    deallocate_matrix_fl(D_l,P[r_par+1]);
  }
}


