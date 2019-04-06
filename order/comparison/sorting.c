#include <stdio.h>


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


int partition(float* v,int left,int r,int p){
    switc(&v[p],&v[left]);
    for(int i=left;i<=r;){
        if(v[i]>v[left]){
            switc(&v[i],&v[r]);
            r=r-1;
        }
        else{i+=1;}
    }
    switc(&v[left],&v[r]);
    return r;
}


void quick_sort(float* v, int left, int r){
    int p;
    while(left<r){
        p=partition(v,left,r,left);
        quick_sort(v,left,p-1);
        left=p+1;
    }
}

void counting_sort(float **A,int size_A, float **B,int k1,int k2){ //to be extended from [0,k] to [k1-k2]
    float **C= calloc(k2-k1,sizeof(float));
    for(size_t i = 0; i < size_A; i++)
    {
        C[A[i]-k1]+=1;
    }
    
    for(size_t j = 1; j < (k2-k1); j++)
    {
        C[j]=C[j-1]+C[j];
    }
    
    for(size_t i = size_A-1; i >=0; i--)
    {
        B[C[A[i]-k1]]=A[i];
        C[A[i]-k1]=C[A[i]-k1]-1;
    }
    free(C);'
}

