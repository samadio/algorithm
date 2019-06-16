#include <stdio.h>
#include <stdlib.h>
#include<float.h>
#include<dijkstra.h>

int left(int i){
    return 2*i+1;
}

int right(int i){
    return 2*i+2;
}

int parent(int i){
    return (i-1)/2;
}

int get_root(node* H){
    return 0;
}

int is_root(int i){
    return i==0;
}

int is_valide_node(node** H,int i,int size){
    return size>i;
}

node* heap_minimum(node** H){
    return H[0];
}

void swap(node** H, int i, int j){
    if(i==j)return;
    node *temp= H[i];
    H[i]=H[j];
    H[j]=temp;

        //update positions
    H[i]->pos = i;
    H[j]->pos = j;
}

void heapify(node**H,int i, int size){
    int m=i;

    for(int j = left(i); j <=right(i); j++)
    { 
        if (is_valide_node(H,j,size) && H[j]->d<H[m]->d) {
            m=j;
        }
    }
    if(i!=m){
        swap(H,i,m);
        heapify(H,m,size);
    }
}

node* remove_minimum(node** H, int size){
    node* min=H[0];
    H[0]=H[size-1];
    heapify(H,0,size-1);
    return min;
}

void build_heap(node** A,int size){
    for(int i =(size-2)/2; i >=0 ; i--)
    {
        heapify(A,i,size);
    }

}

void heap_decrease_key(node** H,int i, double value){
    H[i]->d=value;
    while( !(  is_root(i) || H[parent(i)]->d>=H[i]->d )){
        swap(H,i,parent(i));
        
        i=parent(i);
    }
       
}