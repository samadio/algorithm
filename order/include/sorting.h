#ifndef __SORT__

#define __SORT__

void print_vector(float* v, int len);

void insertion_sort(float* v,int dim);

void quick_sort(float* v, int left, int r);

void build_heap(float* A,int size);

int get_root(float* H);

int is_root(int i);

int is_valide_node(float* H,int i,int size);

float heap_minimum(float* H);

float* heap_insert(float* H, float value,int size);

void heap_sort(float* H,int size);

void counting_sort(float **A,int size_A, float **B,int k1,int k2);

#endif
