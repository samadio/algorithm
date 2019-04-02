#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain.h"
#include "side.h"

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
        //randomly_fill_matrix(A[i],P[i],P[i+1]); //fill each matrix
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
        C=allocate_matrix(P[0],P[i+2]);
        copy_matrix(D,C,P[0],P[i+2]); //prepare new partial results

        deallocate_matrix_fl(D,P[0]);
    }

    deallocate_matrix_fl(C,P[0]);    

    printf("naive time\tnew time\n");
    printf("%lf\t", time);

    time=0;

    printf("%lf\n",time);
    int** s=matrixchain(P,n);


    for(int i = 0; i < (n-1); i++)
    {
        for(int j = 0; j < n-1; j++)
        {
            printf("%d ", s[i][j]);
        }
    printf("\n");    
    }
//checked it give wanted results for both s and m
 





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