#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "sorting_no_comparison.h"
#include "sorting.h"
#include "time.h"

int main(){
  
  
  const size_t n=1<<15; //from 10 to 15
  float* A=create_array_float(n);
  float*B=(float*)malloc(n*sizeof(float));
  copy_vec(B,A,n);
  struct timespec b_time, e_time;
  
  /* test on reverse working
  copy_vec(B,A,n);
  heap_sort_reverse(B,n);

  printf("reverse ordered %d \n", ordered_reverse(B,n));
  */

  float* no_rep=create_norep(n);
  
  printf("size\tworst insert\tbest insert\tworst quick\tbest quick\n");
  
  for(size_t len = 1<<10; len <=n; len=len*2)
  {
    heap_sort_reverse(A,len); //sorted reverse

    clock_gettime(CLOCK_REALTIME, &b_time);
    insertion_sort(A,len);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("%ld\t%lf", len,get_execution_time(b_time, e_time));    
        
    //now A is sorted, let's see best cases
    clock_gettime(CLOCK_REALTIME, &b_time);
    insertion_sort(A,len);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf", get_execution_time(b_time, e_time));    

    //worst quicksort: array already sorted means S is 0 every iteration
    clock_gettime(CLOCK_REALTIME, &b_time);
    quick_sort(A,0,len-1);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf", get_execution_time(b_time, e_time));    

    //copy_vec(A,B,len);
    clock_gettime(CLOCK_REALTIME, &b_time);
    quick_sort_best(no_rep,0,len-1);
    clock_gettime(CLOCK_REALTIME, &e_time);
    printf("\t%lf\t", get_execution_time(b_time, e_time));
    printf("%f\n",ordered_float(no_rep,len)*1.0);    

  }

  printf("\tquadratic\tlinear\t \tquadratic\tn log n\n");
  
  free(A);
  free(B);
  return 0;
}
