#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define MAX 1000

int* create_array(const size_t len){
    int *A=(int*)calloc(len,sizeof(int));
    for(size_t i = 0; i < len; i++)
    {
        A[i]=rand()% MAX;
    }
    return A;
}

double* create_array_double(const size_t len){
    double *A=(double*)calloc(len,sizeof(double));
    for(size_t i = 0; i < len; i++)
    {
        A[i]=(rand()% MAX)/(MAX*1.0);
    }
    return A;
}



double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}



int ordered(int *v,const size_t len){
    int r=1;
    for(size_t i=0;i<len-1;i++){
        if(v[i] > v[i+1]){
            printf("Problem: v[%ld]=%d>v[%ld]=%d\n", i,v[i], i+1,v[i+1]);
            r=0;
        }
    }
    if(v[0]>v[len-1]){r=0;}
    return r;
}


int ordered_double(double *v,const size_t len){
    int r=1;
    for(size_t i=0;i<len-1;i++){
        if(v[i] > v[i+1] && (v[i]-v[i+1])>1e-4){ //to avoid representation problems
            printf("Problem: v[%ld]=%lf>v[%ld]=%lf\n", i,v[i], i+1,v[i+1]);
            r=0;
        }
    }
    if(v[0]>v[len-1]){r=0;}
    return r;
}


