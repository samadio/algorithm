#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain.h"
#include "side.h"

int *build_dimensions(const int n) {
  int *dims = (int *)malloc(sizeof(int) * (n + 1));

  for (size_t i = 0; i < n + 1; i++) {
    dims[i] = rand() % 600;
  }

  return dims;
}

float ***build_problem_instance(const int *dims, const int n) {
  float ***A = (float ***)malloc(sizeof(float **) * n);

  for (size_t i = 0; i < n; i++) {
    A[i] = allocate_matrix(dims[i], dims[i + 1]);
  }

  return A;
}

int main() {
  for(int n=2;n<33;n=n*2){

    int *P = build_dimensions(n);
    float ***A = build_problem_instance(P, n);

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
        C=allocate_matrix(P[0],P[i+2]);
        copy_matrix(D,C,P[0],P[i+2]); //prepare new partial results

        deallocate_matrix_fl(D,P[0]);
    }

    deallocate_matrix_fl(C,P[0]);    

    printf("size\tnaive time\tnew time\n");
    printf("%d\t%lf\t",n, time);

    time=0.0;

    int** s=matrixchain(P,n);

    float **res=allocate_matrix(P[0],P[n]);
    time=using_s(res,A,P,s,0,n-1,&time);
    printf("%lf\n",time);

/*
    for(int i = 0; i < (n-1); i++)
    {
        for(int j = 0; j < n-1; j++)
        {
            printf("%d ", s[i][j]);
        }
    printf("\n");    
    }
*/
//checked it give wanted results for both s and m
 





    //deallocating everything
    for(size_t i = 0; i < n; i++)
    {
        deallocate_matrix_fl(A[i],P[i]);
    }
    free(A);

    //deallocate res
    deallocate_matrix_fl(res,P[0]);

    //deallocate s
    for (size_t i=0; i<n-1; i++) {
    free(s[i]);
    }

    free(s);
    free(P);

  }
  return 0;
}