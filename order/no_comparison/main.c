#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
#include "sorting.h"
#include "no_comparison.h"

#define MAX 500

int* create_array(int len){
    int *A=(int*)calloc(len,sizeof(int));
    for(int i = 0; i < len; i++)
    {
        A[i]=rand()% MAX;
    }
    return A;
}

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int ordered(int *v,int len){
    int r=1;
    for(int i=0;i<len-1;i++){
        if(v[i] > v[i+1]){
            printf("Problem: v[%d]=%d>v[%d]=%d\n", i,v[i], i+1,v[i+1]);
            r=0;
        }
    }
    if(v[0]>v[len-1]){r=0;}
    return r;
}




int main(){
  //int n=1<<29; //from 23 to 29
  int n=2000;
  int* A=create_array(n);
  int *B=(int*)calloc(n,sizeof(int));


  printf("size\tcounting sort\tordered?\tradix sort\tordered?\n");
  for(int len = 1000; len <=2000; len=len*2)
  {
      
    //test for values in [k1,k2]

    //int A[8]={3,5,4,6,2,1,9,10};
    //int max= ; //can be done precisely building heaps w r t to < or > eventually,
    //int min= ; //but it's not the aim    
    struct timespec b_time, e_time;

    clock_gettime(CLOCK_REALTIME, &b_time);
    counting_sort_with_bounds(A,B,len,0,MAX);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("%d\t%lf", len,get_execution_time(b_time, e_time));    
    printf("\t%f", ordered(B,len)*1.0);
    
    clock_gettime(CLOCK_REALTIME, &b_time);
    radix_sort(A,len);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf", get_execution_time(b_time, e_time));    
    printf("\t%f\n", ordered(A,len)*1.0);
    
    

    
  }
  free(B);
  free(A);
  printf("Scaling linearly\n");
  
  return 0;
}