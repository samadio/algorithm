#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"

void print_vector(float* v, int len){
    for(int i=0;i<len;i++){
        printf("%d: %lf  ",i,v[i]);
    }
    printf("\n");

}

void copy_vec(float *v1, float* v2, int len){
    for(int i=0;i<len;i++){
        v1[i]=v2[i];
    }
}


double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int ordered(float *v,int len){
    int r=1;
    for(int i=0;i<len-1;i++){
        if(v[i] > v[i+1]){
            printf("Problem at idx: %d", i);
            r=0;}
    }
    if(v[0]>v[len-1]){r=0;}
    return r;
}

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

    for(int len=1<<10;len<n;len=len*2){
        struct timespec b_time, e_time;
        printf("size\tinsertion time\tquick_sort\t ordered?\n");

        ////NAIVE
        clock_gettime(CLOCK_REALTIME, &b_time);
        insertion_sort(v,len);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("%d\t%lf", len,get_execution_time(b_time, e_time));
        
        //reinitialize v to original value
        copy_vec(v,tmp,len);

        //quicksort
        clock_gettime(CLOCK_REALTIME, &b_time);
        quick_sort(v,0,len-1);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("\t%lf", get_execution_time(b_time, e_time));

        printf("\t%d\n", ordered(v,len));

    }
    free(v);
    free(tmp);
    return 0;
}