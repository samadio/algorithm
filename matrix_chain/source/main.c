#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain.h"
#include "utils.h"

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
  for(int n=10;n<100;n=n+10){

    int *P = build_dimensions(n);
    float ***A = build_problem_instance(P, n);

    //matrixes for partial results
    float **C=allocate_matrix(P[0],P[1]);
    copy_matrix(A[0],C,P[0],P[1]);

    //time stuff
    struct timespec b_time, e_time;
    double time=0.0;
    

    clock_gettime(CLOCK_REALTIME, &b_time);     
    //naive ordered matrix_multiplication
    for(size_t i = 0; i < n-1; i++)
    {
        float **D=allocate_matrix(P[0],P[i+2]);  //allocate new D
        


        naive_matrix_mult(D,C,A[i+1],P[0],P[i+1],P[i+1],P[i+2]);
   
        
        deallocate_matrix_fl(C,P[0]); //free partial results
        C=allocate_matrix(P[0],P[i+2]);
        copy_matrix(D,C,P[0],P[i+2]); //prepare new partial results

        deallocate_matrix_fl(D,P[0]);
    }

    deallocate_matrix_fl(C,P[0]);    

    clock_gettime(CLOCK_REALTIME, &e_time);

    time=get_execution_time(b_time, e_time);


    printf("size\tnaive time\tnew time\n");
    printf("%d\t%lf\t",n, time);


    int** s=matrixchain(P,n);

    clock_gettime(CLOCK_REALTIME, &b_time); 

    float **res=allocate_matrix(P[0],P[n]);
    using_s(res,A,P,s,0,n-1);

    clock_gettime(CLOCK_REALTIME, &e_time); 


    time=get_execution_time(b_time, e_time);

    printf("%lf\n",time);


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
