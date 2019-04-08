#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"sorting.h"
#include"no_comparison.h"

void switc(int* a, int* b){
    if(*a==*b){return;}
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}



void counting_sort_with_bounds(int *A,int* B, int len,int low, int up){
    int *C=(int*)calloc(1+up-low,sizeof(int));
    for(int i = 0; i < len; i++) //read all of A
    {
        C[A[i]-low]=C[A[i]-low]+1; //place it into C[0,..,up-low]
    }

    for(int i = 1; i <= up-low; i++)
    {
        C[i]=C[i-1]+C[i];
    }


    for(int i = len-1; i>=0; i=i-1)
    {   
        C[A[i]-low]=C[A[i]-low]-1;
        B[C[A[i]-low]]=A[i];
    }


    

    free(C);
    
}


void radix_sort(int *A,int size){
  //shift is digit taken in account
  int shift=1;
  int count=0;
  while(count!=size)
  {
    for(size_t i = 0; i < size; i++) //pick an element of the array
    {
        count=0;
        for(size_t j = 0; j < i+1; j++) //read all the other element of the array
        {
            if((A[i]%(int)pow(10,shift))/pow(10,shift-1)<(A[j]%(int)pow(10,shift))/pow(10,shift-1) && i>j)
            {
                switc(&A[i],&A[j]);
            }
            if(A[j]/(int)pow(10,shift)==0){count+=1;} //count how many elements have shift digits
        }
    }
    shift+=1;
  }
}


/*
int select_pivot(*A,int l=1,int r=len(A)){
    for(size_t i = 0; i <= (r-l)/5; i++)
    {
        insertion_sort(A,5*i+l,min(5*i+l+4,r));
    }
    
    for(size_t i = 0; i <= (r-l)/5; i++)
    {
        swap(A,l+i,max(5*i+l+2,r)); //swap all the medians all togheter at the beginning of A
    }

    return select(A, ((r-l)/5+1)*0.5, l, l+ (r-l)/5);
}


//this algoithm allows u to choose the best pivot-> best case scenario: quicksort= theta(nlog n)
//if r<140 u use another algorithm to have linearity?
int select(*A,int i,int l=1,int r=len(A)){ //l where to start from, r where to stop looking
    j=select_pivot(A,l,r);
    k=partition(A,l,r,j);
    if(i==k) return k;
    if(i<k) return select(A,i,l,k-1); //look in S
    return select(A,i,k+1,r);   //look in G
}
*/