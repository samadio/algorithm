
#include <stdio.h>
#include <stdlib.h>
#include<float.h>
#include "sorting.h"

void print_vector(float* v, int len){
    for(int i=0;i<len;i++){
        printf("%d: %lf  ",i,v[i]);
    }
    printf("\n");

}


int left(int i){
    return 2*i+1;
}

int right(int i){
    return 2*i+2;
}

int parent(int i){
    return (i-1)/2;
}

int get_root(float* H){
    return 0;
}

int is_root(int i){
    return i==0;
}

int is_valide_node(float* H,int i,int size){
    return size>i;
}

float heap_minimum(float* H){
    return H[0];
}

void swap(float* H, int i, int j){
    if(i==j)return;
    *(H+i)=*(H+j)+*(H+i);
    *(H+j)=*(H+i)-*(H+j);
    *(H+i)=*(H+i)-*(H+j);
}

void heapify(float *H,int i, int size){
    int m=i;

    for(int j = left(i); j <=right(i); j++)
    { 
        if (is_valide_node(H,j,size) && H[j]>=H[m]) {
            m=j;
        }
    }
    if(i!=m){
        swap(H,i,m);
        heapify(H,m,size);
    }
}


void remove_minimum(float* H, int i,int size){
    H[0]=H[size-1];
    heapify(H,0,size-1);
}

void build_heap(float* A,int size){
    for(int i =(size-2)/2; i >=0 ; i--)
    {
        heapify(A,i,size);
    }

}

void heap_decrease_key(float* H,int i, float value){
    if( H[i]>=value){
        printf("value:%f is not greater than H[%d]:%f \n", value, i, H[i]);
        //1/0;
        return;
    }
    H[i]=value;
    while( !(  is_root(i) || H[parent(i)]>=H[i] )){
        swap(H,i,parent(i));
        i=parent(i);
    }
       
}

float* heap_insert(float* H, float value,int size){
    int newsize=size+1;
    float* new=(float*)malloc(sizeof(float)*newsize);
    for(size_t i = 0; i < newsize-1; i++)
    {
        new[i]=H[i];
    }
    new[newsize]=-FLT_MAX;
    heap_decrease_key(new,newsize,value);
    free(H);
    return new;
}

void heap_sort(float* H,int size){
    build_heap(H,size);

    for(size_t i = size-1; i >=1; i--)
    {
        swap(H,0,i);
        size=size-1;
        heapify(H,0,size);
    }
    
}


///reverse ordering

void heapify_reverse(float *H,int i, int size){
    int m=i;

    for(int j = left(i); j <=right(i); j++)
    { 
        if (is_valide_node(H,j,size) && H[j]<=H[m]) {
            m=j;
        }
    }
    if(i!=m){
        swap(H,i,m);
        heapify(H,m,size);
    }
}

void heap_sort_reverse(float* H,int size){
    build_heap(H,size);

    for(size_t i = size-1; i >=1; i--)
    {
        swap(H,0,i);
        size=size-1;
        heapify_reverse(H,0,size);
    }
    
}