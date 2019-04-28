#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"sorting_no_comparison.h"

void double_switch(double* a, double* b){
    if((*a)==(*b)){return;}
    (*a)=(*a)+(*b);
    (*b)=(*a)-(*b);
    (*a)=(*a)-(*b);
}


////////////////////////////////////////counting sort //////////////////////////////////////////////

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


////////////////////////////radix sort////////////////////////////////////

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

//////////////////////////////////////bucket sort//////////////////////////////

int partition_double(double* v,const int left,const int r,const int p){
    int i,j;
    i=left+1;
    j=r;
    while(i<=j){
        if (v[i]<=v[left]){i+=1;} //first element it's okay
        else if(v[j]>v[left]){j-=1;}  //last element fine
        else{
            double_switch(&v[i],&v[j]);
            i+=1;
            j-=1;
        }
    }
    double_switch(&v[j],&v[left]);
    return j;
}


void quick_sort_double(double* v, int left, const int r){
    int p;
    while(left<r){
        p=partition_double(v,left,r,left);
        quick_sort_double(v,left,p-1);
        left=p+1;
    }
}


void bucket_sort(double*A,const size_t size){ 
    const size_t n=size;  //n=number of buckets
    double**B=(double**)malloc(n*sizeof(double*));  //array of n buckets

    size_t j;  //bucket idx
    size_t* it=(size_t*)calloc(size,sizeof(size_t)); //it[j] will be identifier of each number in bucket j, at the end will be size of bucket j;
        
    for (size_t i = 0; i < size; i++)
    {
        j=(size_t)floor(A[i]*n); //bucket id for element i in A
        it[j]+=1;   //number of elements in bucket j increases   
    }

    for (size_t j = 0; j < n; j++)
    {
        B[j]=(double*)malloc(it[j]*sizeof(double)); //allocate the exact amount
        it[j]=0;
    }

    for (size_t i = 0; i < size; i++)
    {
        j=(size_t)floor(A[i]*n); //bucket id for element i in A
        B[j][it[j]]=A[i];
        it[j]++;   
    }    
    
    for (size_t j = 0; j < n; j++) //order each bucket B[j]
    {
        int toint= it[j];  //should have no overflow, I expect to have 1 element for bucket
        quick_sort_double(B[j],0,toint-1);
    }
    
    size_t idx=0;
    for (size_t j = 0; j < n; j++) //for each bucket j
    {
        for (size_t k = 0; k < it[j]; k++)  //for each element B[j][k] in bucket j
        {
            A[idx]=B[j][k];
            idx+=1;
        }
    }

    for (size_t j = 0; j < n; j++)
    {
        free(B[j]);
    }
    free(B);
    free(it);
    
}
