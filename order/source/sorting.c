#include <stdio.h>
#include<stdlib.h>
#include<math.h>

void switc(float* a, float* b){
    if(*a==*b){return;}
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}

void insertion_sort(float* v,int dim){
    for(int i=1;i<dim;i++){
        int j=i;
        while(v[j]<v[j-1]){
            switc(&v[j],&v[j-1]);
            j=j-1;
        }
    }
}

int partition(float* v,int left,int r,int p){ //partition v from left to r into values smaller of v[p] and bigger than v[p]
    int i,j;
    switc(&v[p],&v[left]);
    i=left+1;
    j=r;
    while(i<=j){
        if (v[i]<=v[left]){
            i++;
        }
        else if(v[j]>v[left]){
            --j;
        }
        else{
            switc(&v[i],&v[j]);
            ++i;
            --j;
        }
    }
    switc(&v[j],&v[left]);
    return j;
}




void quick_sort(float* v, int left, int r){ //r is the last valid index of the array, it's dimension-1
    int p;
    while(left<r){
        p=partition(v,left,r,left);
        quick_sort(v,left,p-1);
        left=p+1;
    }
}




//////////////////////////////////////////////////select pivot////////////////////////////////



void insertion_sort_pivot(float* v,int start,int end){ //end excluded
    for(int i=start+1;i<end;i++){
        int j=i;
        while(v[j]<v[j-1]){
            switc(&v[j],&v[j-1]);
            j=j-1;
        }
    }
}


int min(int a, int b){
    if(a>b)return b;
    return a;
}


int select_pivot(float *A,int l,int r){ //r included
    if(r-l<=4){
        quick_sort(A,l,r);
        return (l+r+1)/2;
    }
    
    int chunks=(r-l)/5+1;

    int local_end=l+4;
    while(local_end<=r+4)
    {
        insertion_sort_pivot(A,local_end-4,min(local_end+1,r+1));  //sort each chunk, for N=5, I can use whatever
        local_end+=5;
    }
    
    for(int i = 0; i < chunks; i++)
    {
        switc(&A[l+i],&A[min(5*i+l+2,r)]); //put medians firsts
    }

    int m=select_pivot(A,l,l+chunks-1);
    return m;
}

int partition_greater(float* v,int left,int r,int p){ //just like partition, put values equal to pivot are stored in G, so that I have globally [S,pivot,G] 
    int i,j;
    switc(&v[p],&v[left]);
    i=left+1;
    j=r;
    while(i<=j){
        if (v[i]-v[left]<0.00001){ //data generated between 0 and 1 with distance 10^-5
            i++;
        }
        else if(v[j]-v[left]>-0.00001){   //it's like greater or equal 0
            --j;
        }
        else{
            switc(&v[i],&v[j]);
            ++i;
            --j;
        }
    }
    switc(&v[j],&v[left]);
    return j;
}


float selection(float *A,int i,int l,int r){ //l where to start from, r where to stop looking, r included
    if(l==r) return A[l];
    int j=select_pivot(A,l,r); //choose pivot
    
    int k=partition(A,l,r,j);  //k is the index of j in sorted_A
    
    if(i>k) return selection(A,i,k+1,r);   //look in G
    int first_occurrency=partition_greater(A,l,k,k);  //otherwise divide S between S and pivot occurrencies
    if(first_occurrency<=i && i<=k) return A[k];
    k=first_occurrency;
    if(i<k) return selection(A,i,l,k-1); //look in S without pivot
    
}

/*
void quick_sort_best_with_repetitions(float* v, int left, int r){
    int p,selected;
    while(left<r){
        selected= select_pivot(v,left,r);
        p=partition(v,left,r,selected);
        int f_occ=partition_greater(v,left,p,p);
        quick_sort_best_with_repetitions(v,left,f_occ-1); //sort before pivot occurrencies
        left=p+1;
    }
}*/

void quick_sort_best(float* v, int left, int r){
    while(left<r){
        int p=partition(v,left,r,(left+r)/2);
        quick_sort_best(v,left,p-1); //sort before pivot occurrencies
        left=p+1;
    }
}
