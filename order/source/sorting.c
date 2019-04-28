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


int partition(float* v,int left,int r,int p){
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


void quick_sort(float* v, int left, int r){
    int p;
    while(left<r){
        p=partition(v,left,r,left);
        quick_sort(v,left,p-1);
        left=p+1;
    }
}




//////////////////////////////////////////////////select pivot////////////////////////////////



void insertion_sort_pivot(float* v,int start,int end){
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


int select_pivot(float *A,int l,int r){
    if(r-l<5){
        quick_sort(A,l,r);
        return (l+r)/2;
    }
    
    int chunks=(1+r-l+4)/5;
    for(int i = 0; i < chunks; i++)   // i is index of chunk
    {
        insertion_sort_pivot(A,5*i+l,min(5*i+l+4,r));  //sort each chunk
    }
    
    for(int i = 0; i < chunks; i++)
    {
        switc(&A[l+i],&A[min(5*i+l+2,r)]); //put medians firsts
    }

    int m=select_pivot(A,l,l+chunks);
    return m;
}


float selection(float *A,int i,int l,int r){ //l where to start from, r where to stop looking
    if(l==r) return A[l];
    int j=select_pivot(A,l,r); //choose pivot
    
    int k=partition(A,l,r,j);  //k is the index of j in sorted_A
    
    if(i==k) return A[k];
    if(i<k) return selection(A,i,l,k-1); //look in S
    if(i>k) return selection(A,i,k+1,r);   //look in G
    
}

void quick_sort_best(float* v, int left, int r){
    int p,selected;
    while(left<r){
        selected= select_pivot(v,left,r);
        p=partition(v,left,r,selected);
        quick_sort_best(v,left,p-1);
        left=p+1;
    }
}
