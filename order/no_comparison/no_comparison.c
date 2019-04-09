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

int max_digits(int* A, int size){
    int count=0;
    int d=1;
    while(count<size){
        count=0;
        int mod=(int)pow(10,d);
        int den=(int)pow(10,d-1);
        for(size_t i = 0; i < size; i++) //read all the array
        {
            if(   (A[i]%mod)<den && A[i]<den){ //if first term is 0, then A[i] has d-1 digits
                           //second if term checks if I encountered a zero in the middle of a number 
                count+=1; //number of elements with d-1 digits
            }
        }
        d+=1;
    }
    return d-2;
}

int get_digit(int num, int d){
    if(d==0){
        printf("Digits are counted from 1, from right to left");
    }
    return (num%(int)pow(10,d))/pow(10,d-1);
}

void radix_sort(int *A,int size){ //to order without knowing digits
  int d=max_digits(A,size);  //now I know number of digits
  int **B=(int **)malloc(sizeof(int*)*d);

  for (size_t i=0; i<d; i++) {
      B[i]=(int *)calloc(size,sizeof(int));
  }
  

  for(size_t k = 1; k <= d; k++)
  {  
    for(size_t i = 0; i < size; i++) //pick an element of the array
    {
       B[k-1][i]=get_digit(A[i],k); 
    }
  }


  for(size_t k = 1; k <=d ; k++)
  {
      printf("safe zone\n");
      counting_sort_with_bounds(B[k-1],B[k-1],size,0,9);
  }

  for(size_t i = 0; i < size; i++)
  {
     A[i]=0; 
     for(size_t k = 1; k <= d; k++)
     {
         A[i]+= B[k-1][i];
     }
  }



  for(size_t i = 0; i <d; i++)
  {
      free(B[i]);
  }
  free(B);
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