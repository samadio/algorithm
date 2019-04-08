#ifndef __NOCOMP__

#define __NOCOMP__

void counting_sort_with_bounds(int *A,int* B, int len,int low, int up);
int max_digits(int *A,int size);
void radix_sort(int *A,int size, int digits);
void quadratic_radix_sort(int *A,int size);
void switc(int* a, int* b);
//int select_pivot(*A,int l=1,int r=len(A));
//int select(*A,int i,int l=1,int r=len(A));

#endif