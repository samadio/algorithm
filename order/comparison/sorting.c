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
    int i,j;
    i=left+1;
    j=r;
    while(i<=j){
        if (v[i]<=v[left]){i+=1;} //first element it's okay
        else if(v[j]>v[left]){j-=1;}  //last element fine
        else{
            switc(&v[i],&v[j]);
            i+=1;
            j-=1;
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
