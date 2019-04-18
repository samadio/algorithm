#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"sorting.h"
#include"no_comparison.h"

void double_switch(double* a, double* b){
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
    int shift = 1; //digit considered as power of 10
    int new[size];

    for(shift=1;shift<=pow(10,d);shift=shift*10){
        int C[10] = {0};
        for (int i = 0; i < size; i++)
            C[ (A[i]/shift)%10 ]+=1; //number of occurrences for each of the 10 digits
            //A[i]/shift%10 == digit of the power 10**shift

        //similar to counting_sort
        for (int i = 1; i < 10; i++)
            C[i] += C[i - 1];

        // Build the sorted array as in counting_sort
        for (int i = size - 1; i >= 0; i--)
        {
            new[C[ (A[i]/shift)%10 ]-1] = A[i];
            C[ (A[i]/shift)%10 ]-=1;
        }

        //new now contains the sorted result, so update A
        for (int i = 0; i < size; i++)
            A[i] = new[i];
        // shift increases: next digit
    }
}



size_t partition(double* v,const size_t left,size_t r,size_t p){
    double_switch(&v[p],&v[left]);
    for(size_t i=left;i<=r;){
        if(v[i]>v[left]){
            double_switch(&v[i],&v[r]);
            r=r-1;
        }
        else{i+=1;}
    }
    double_switch(&v[left],&v[r]);
    return r;
}



void bucketsort_aux(double* v,size_t left,const size_t r) {   //quick_sort with doubles.
    size_t p;
    while(left<r){
        p=partition(v,left,r,left);
        bucketsort_aux(v,left,p-1);
        left=p+1;
    }
}

//not efficient in terms of memory, still linear and easily explicable
void bucket_sort(double*A,const size_t size,const size_t n){  //n=number of buckets
    double**B=(double**)malloc(n*sizeof(double*));  //array of n buckets

    for (size_t i = 0; i < n; i++)
    {
        B[i]=(double*)malloc(size*sizeof(double));  //in principle, each of the n buckets can contain the whole array
    }
    
    size_t j;  //bucket idx
    size_t* it=(size_t*)calloc(size,sizeof(size_t)); //it[j] will be identifier of each number in bucket j, at the end will be size of bucket j;
    
    for (size_t i = 0; i < size; i++)
    {
        j=(size_t)floor(A[i]*n); //bucket id for element i in A
        B[j][it[j]]=A[i];
        it[j]+=1;   //number of elements in bucket j        
    }
    
    for (size_t j = 0; j < n; j++) //order each bucket B[j]
    {
        bucketsort_aux(&(B[j][0]),0,it[j]-1);
    }
    

    size_t idx=0;
    for (size_t j = 0; j < n; j++) //for each bucket
    {
        for (size_t k = 0; k < it[j]; k++)  //for each element in bucket
        {
            A[idx]=B[j][k];
            idx+=1;
        }
    }

    /*  printf("fine\n");
    for (size_t j = 0; j < n; j++)
    {
        free(B[j]);
    }
    printf("fine\n");
    free(B);
    printf("fine\n");
    free(it);
    printf("fine\n");
    */
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