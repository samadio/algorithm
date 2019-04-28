#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"
#include "utils.h"

int main()
{
    int n=1<<17;
    float *v=(float *)malloc(sizeof(float)*n);
    
    //initialization
    for(int i=0;i<n;i++){
        v[i]= rand()%(1<<10)/((1<<10)*1.0);
    }

    float *tmp=(float *)malloc(sizeof(float)*n);
    copy_vec(tmp,v,n);
    struct timespec b_time, e_time;
    printf("size\tinsertion time\tquick_sort\tordered?\theap_sort\tordered?\n");

    for(int len=1<<10;len<n;len=len*2){

        ////NAIVE
        clock_gettime(CLOCK_REALTIME, &b_time);
        insertion_sort(v,len);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("%d\t%lf", len,get_execution_time(b_time, e_time));
        
        //reinitialize v to original values
        copy_vec(v,tmp,len);

        //quicksort
        clock_gettime(CLOCK_REALTIME, &b_time);
        quick_sort(v,0,len-1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));

        printf("\t%f", ordered_float(v,len)*1.0);

        //reinitialize v to original values
        copy_vec(v,tmp,len);

        //heapsort
        clock_gettime(CLOCK_REALTIME, &b_time);
        heap_sort(v,len);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));
        printf("\t%f\n", ordered_float(v,len)*1.0);

        

    }
    free(v);
    free(tmp);

    return 0;
}
