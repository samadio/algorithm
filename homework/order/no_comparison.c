#include<stdio.h>
#include<math.h>
#include"sorting.h"
#include"no_comparison.h"

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