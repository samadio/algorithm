#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
#include "sorting_no_comparison.h"
#include "utils.h"

#define MAX 100000

int main(){
  
  
  const size_t n=1<<20; //from 15 to 20
  int* A=create_array(n);
  int *B=(int*)calloc(n,sizeof(int));
  int* A2=create_array(n);
  double* A3=create_array_double(n);

  printf("size\tcounting sort\tordered?\tradix sort\tordered?\tbucket sort\tordered?\n");
  for(size_t len = 1<<15; len <=n; len=len*2)
  {
      
    struct timespec b_time, e_time;

    clock_gettime(CLOCK_REALTIME, &b_time);
    counting_sort_with_bounds(A,B,len,len*0,MAX);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("%ld\t%lf", len,get_execution_time(b_time, e_time));    
    printf("\t%f", ordered(B,len)*1.0);
  
    
    clock_gettime(CLOCK_REALTIME, &b_time);
    radix_sort(A2,len);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf", get_execution_time(b_time, e_time));    
    printf("\t%f", ordered(A2,len)*1.0);
    

    clock_gettime(CLOCK_REALTIME, &b_time);
    bucket_sort(A3,len);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf", get_execution_time(b_time, e_time));    
    printf("\t%f\n", ordered_double(A3,len)*1.0);

    
  }

  /*
  int* test=(int*)malloc(5*sizeof(int));
  test[0]=3;
  test[1]=2;
  test[2]=1;
  test[3]=6;
  test[4]=4;

  for (size_t i = 0; i < 5; i++)
  {
      printf("%d ",selection(test,i,0,4));
  }
  printf("\n");  
  free(test);
  */
  free(B);
  free(A);
  free(A2);
  free(A3);
  
  printf("Scaling linearly\n");
  
  return 0;
}
